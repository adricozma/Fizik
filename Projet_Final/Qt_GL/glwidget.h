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

  void ajoute(Balle b) {b.ajoute(S);}
  void ajoute(Boulet boul) {boul.ajoute(S);}
  void ajoute(Caillou c) {c.ajoute(S);}
  void ajoute(Pendule p) {p.ajoute(S);}
  void ajoute(PenduleSpherique p) {p.ajoute(S);}
  void ajoute(Ressort r) {r.ajoute(S);}
  void ajoute(PlanFini p) {p.ajoute(S);}
  void ajoute(PlanInfini pi) {pi.ajoute(S);}
  void ajoute(Brique b) {b.ajoute(S);}
  void ajoute(Sphere s) {s.ajoute(S);}
  void ajoute(Terrain s) {s.ajoute(S);}
  void ajoute(Ventilateur v) {v.ajoute(S);}
  
  void ajoute(ChampForces c) {c.ajoute(S);}
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

};
