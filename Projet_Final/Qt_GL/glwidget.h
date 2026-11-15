#pragma once

#include <QOpenGLWidget>        // Classe pour faire une fenêtre OpenGL
#include <QTime>				// Classe pour gérer le temps
//~ #include "Vecteur.h"								
#include "vue_opengl.h"
//~ #include "ObjetMobile.h"
#include "Systeme.h"
//~ #include "Obstacle.h"
#include "ObjetCompose.h"
#include "ChampForces.h"
//~ #include "constantes.h"
//~ #include "Integrateur.h"
#include <cmath>
#include <functional>
#include <vector>
class GLWidget : public QOpenGLWidget
/* La fenêtre hérite de QOpenGLWidget ;
 * les événements (clavier, souris, temps) sont des méthodes virtuelles à redéfinir.
 */
{
public:
  GLWidget(QWidget* parent = nullptr)
    : QOpenGLWidget(parent)
  {setMouseTracking(true);}
  
  virtual ~GLWidget() = default;
  
//Differentes méthodes pour ajouter des objets au système qui 
//	st un attribut prrrivé

  template <typename T>
  void ajoute_et_enregistre(T obj) {
    obj.ajoute(S);
    initializers_.push_back([obj](Systeme& sys) mutable { obj.ajoute(sys); });
  }

  void ajoute(Balle b) { ajoute_et_enregistre(b); }
  void ajoute(Boulet boul) { ajoute_et_enregistre(boul); }
  void ajoute(Caillou c) { ajoute_et_enregistre(c); }
  void ajoute(Pendule p) { ajoute_et_enregistre(p); }
  void ajoute(PenduleSpherique p) { ajoute_et_enregistre(p); }
  void ajoute(Ressort r) { ajoute_et_enregistre(r); }
  void ajoute(PlanFini p) { ajoute_et_enregistre(p); }
  void ajoute(PlanInfini pi) { ajoute_et_enregistre(pi); }
  void ajoute(Brique b) { ajoute_et_enregistre(b); }
  void ajoute(Sphere s) { ajoute_et_enregistre(s); }
  void ajoute(Terrain s) { ajoute_et_enregistre(s); }
  void ajoute(Ventilateur v) { ajoute_et_enregistre(v); }
  
  void ajoute(ChampForces c) { ajoute_et_enregistre(c); }
  //double increment;
  
private:
  // Les 3 méthodes clés de la classe QOpenGLWidget à réimplémenter
  virtual void initializeGL()                  override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL()                       override;

  // Méthodes de gestion d'évènements
  virtual void keyPressEvent(QKeyEvent* event) override;
  virtual void timerEvent(QTimerEvent* event)  override;
  virtual void mousePressEvent(QMouseEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent* event)  override;
  // Méthodes de gestion interne
  
  void pause();
  void restart();

  // Vue : ce qu'il faut donner au contenu pour qu'il puisse se dessiner sur la vue
  VueOpenGL vue;
  //attribut pour la position de la souris
  QPoint lastMousePosition;
  // Timer
  int timerId;
  // pour faire évoluer les objets avec le bon "dt"
  QTime chronometre;
	
  //Differents intégrateurs
  Integrateur I;
  IntegrateurEulerCromer I1;
  IntegrateurRungeKutta I2;
  //Systeme qui contient tous les objets
  Systeme S;
  std::vector<std::function<void(Systeme&)>> initializers_;

};
