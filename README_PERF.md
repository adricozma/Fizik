# Branche `optimisation-perf` : analyse et accélération du rendu 3D

Cette branche part de `main` (code original de 2022) et corrige les goulots d'étranglement qui rendaient la simulation de terrain (Everest, 70×70 points, 20 cailloux) lente sur machine locale (~5 FPS → 50 FPS).

Toutes les modifications dans le code C++ sont marquées par `// [PERF]`.

---

## 1. Goulot GPU : ~19 000 appels `glBegin/glEnd` + `cout` par image

### Problème (`Qt_GL/vue_opengl.cc`)
Dans `VueOpenGL::dessineTerrainMesh`, le maillage était redessiné **2 fois par image** (fil de fer blanc + remplissage noir) en appelant `dessineTriangle()` (~9 500 fois par passe), avec pour chaque triangle :
- `prog.setUniformValue(...)`,
- `glBegin(GL_TRIANGLES)` / `glEnd()`,
- un `cout << ... << endl;` oublié dans la boucle (~9 500 lignes affichées par image).

De plus, `getPointsDessin()` et `dessineTerrainMesh()` passaient le `std::vector<Vecteur>` (~4 900 points) **par valeur**, provoquant ~9 800 copies de vecteurs à chaque image.

### Solution : `QOpenGLBuffer` (VBO) + passage par `const&`
Les sommets du terrain sont envoyés **une seule fois** dans un *Vertex Buffer Object* sur le GPU, puis dessinés en un seul appel `glDrawArrays` :

```cpp
// Qt_GL/vue_opengl.h
QOpenGLBuffer terrain_vbo;
int terrain_vertex_count = 0;
bool terrain_vbo_ready = false;
```

```cpp
// Qt_GL/vue_opengl.cc — VueOpenGL::dessineTerrainMesh(...)
if (!terrain_vbo_ready) {
    QVector<GLfloat> vertices;
    vertices.reserve(static_cast<int>(18 * (lignes - 1) * (lignes - 1)));
    // ... remplissage unique des triangles dans vertices ...
    terrain_vertex_count = vertices.size() / 3;
    terrain_vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    terrain_vbo.create();
    terrain_vbo.bind();
    terrain_vbo.allocate(vertices.constData(),
                         vertices.size() * static_cast<int>(sizeof(GLfloat)));
    terrain_vbo.release();
    terrain_vbo_ready = true;
}

prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
prog.setAttributeValue(CouleurId, r, v, b);
terrain_vbo.bind();
prog.setAttributeBuffer(SommetId, GL_FLOAT, 0, 3);
prog.enableAttributeArray(SommetId);
glDrawArrays(GL_TRIANGLES, 0, terrain_vertex_count);
prog.disableAttributeArray(SommetId);
terrain_vbo.release();
```

---

## 2. Goulot CPU / disque : relecture du fichier `.txt` à chaque image et pour chaque balle

### Problème (`general/Obstacle.cc`)
À chaque pas de temps et pour **chaque** objet mobile (`20` cailloux), `Terrain::agit_sur()` appelle `Terrain::N_plus_proches()` (et `Terrain::point_plus_proche()` existait sur le même modèle). Ces deux méthodes **rouvraient le fichier `f_points_` sur le disque** (`ifstream`) et appelaient `std::stod()` sur les ~4 900 lignes (~98 000 lectures/conversions par image), en calculant la racine carrée `norme()` à chaque point.

### Solution : cache mémoire `points_collision_` + `norme2()`
Le fichier `f_points_` est chargé **une seule fois** dans le constructeur `Terrain::Terrain(...)` :

```cpp
// general/Obstacle.h
std::vector<Vecteur> points_collision_;
```

```cpp
// general/Obstacle.cc — Terrain::N_plus_proches(...)
const Vecteur& pos = o.getPosition();
double best_d2 = (pos - points_collision_[0]).norme2();
for (size_t i = 1; i < points_collision_.size(); ++i) {
    double d2 = (pos - points_collision_[i]).norme2();
    if (d2 < best_d2) {
        best_d2 = d2;
        N_points.push_back(points_collision_[i]);
    }
}
```

Le `cout` de debug dans `Terrain::agit_sur()` a également été commenté.

---

## 3. Intégrateur et stabilité (`Qt_GL/glwidget.cc`)

- Passage d'Euler-Cromer (`I1`, 1 pas de taille `dt` non bornée) à **Runge-Kutta (`I2`) avec 4 sous-pas** et `dt` plafonné à `0.02 s` :
  ```cpp
  double dt_clamped = (dt > 0.02) ? 0.02 : dt;
  vue.setDt(dt_clamped);
  S.evolue(I2, 4, dt_clamped / 4.0);
  ```
  Cela évite qu'une balle traverse le terrain (*tunneling*) lors d'un pic de latence ou à grande vitesse.

---

## 4. Scène de démonstration (`Qt_GL/main_qt_gl.cc` & `initializePosition()`)

- Scène **Everest** activée avec **20 cailloux** (rayon `1.5`) répartis sur les deux versants (`X ∈ [-26, +14]`, `Y ∈ [-28, +2]`, `Z = 58`).
- Caméra initiale (`VueOpenGL::initializePosition()`) centrée face à l'Everest.

---

## 5. Compiler et lancer cette branche (toutes plateformes)

Prérequis : **Qt 5** (5.15.2 recommandé, voir la section *Installation* de [`README.md`](README.md)).

### macOS
```bash
git clone -b optimisation-perf https://github.com/adricozma/Fizik.git
cd Fizik
chmod +x build.sh
./build.sh 3d
```
*(Si le dépôt est déjà cloné localement : `git checkout optimisation-perf && ./build.sh 3d`.)*

### Linux (Debian / Ubuntu)
```bash
git clone -b optimisation-perf https://github.com/adricozma/Fizik.git
cd Fizik
chmod +x build.sh
./build.sh 3d
```

### Windows 10/11 (MinGW, invite de commandes `cmd`)
Après avoir installé Qt 5.15.2 + MinGW (voir [`README.md`](README.md)) :
```bat
set PATH=C:\Qt\5.15.2\mingw81_64\bin;C:\Qt\Tools\mingw810_64\bin;%PATH%
git clone -b optimisation-perf https://github.com/adricozma/Fizik.git
cd Fizik
mkdir build
cd build
qmake ..\Projet_Final\Projet_Final.pro CONFIG+=release
mingw32-make
cd ..\Projet_Final\Qt_GL
..\..\build\Qt_GL\release\Simulations.exe
```
*(Lancer `mingw32-make` sans `-j`, et exécuter `Simulations.exe` depuis `Projet_Final\Qt_GL` pour que les chemins relatifs vers `../height_data/` fonctionnent.)*
