#pragma once
#include <iostream>
#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include "support_a_dessin.h"
#include "Vecteur.h"
#include "glsphere.h"

class VueOpenGL : public SupportADessin {
 public:
  // méthode(s) de dessin (héritée(s) de SupportADessin)
 //======================================================================================================================== 
  virtual void dessine(Balle const& a_dessiner) override;
  virtual void dessine(Boulet const& a_dessiner) override;
  
  virtual void dessine(Ressort const& a_dessiner) override;
  
  virtual void dessine(PlanFini const& a_dessiner) override;
  virtual void dessine(PlanInfini const& a_dessiner) override;
  
  virtual void dessine(Systeme const& a_dessiner) override;
  
  virtual void dessine(Pendule const& a_dessiner) override;
  virtual void dessine(PenduleSpherique const& a_dessiner) override;
 
  virtual void dessine(Brique const& a_dessiner) override;
 
  virtual void dessine(Sphere const& a_dessiner) override;
  virtual void dessine(Terrain const& a_dessiner) override;
  
  virtual void dessine(Ventilateur const& a_dessiner) override;
 //======================================================================================================================== 
  // méthodes de (ré-)initialisation
  void init();
  void initializePosition();

  // méthode set
  void setProjection(QMatrix4x4 const& projection)
  { prog.setUniformValue("projection", projection); }

  // Méthodes set
  void translate(double x, double y, double z);
  void rotate(double angle, double dir_x, double dir_y, double dir_z);
  
  void setDt(double d) {dt+=d;}
  //Methodes utilitaires necessaires pour au méthodes "dessine(a_dessiner)"
 //======================================================================================================================== 
  void dessineBrique(QMatrix4x4 const& point_de_vue,Vecteur o,Vecteur L,Vecteur l,Vecteur n, double h, 
																			double r=0.5, double v=0.5,  double b=0.5);
  void dessineCube(QMatrix4x4 const& point_de_vue = QMatrix4x4(),double r=0.5, double v=0.5,  double b=0.5);
  
  void dessinePlanfini(QMatrix4x4 const& point_de_vue = QMatrix4x4(),Vecteur o={0,0,0},
																				  Vecteur L={1,0,0}, Vecteur l={0,1,0});
  void dessineAxes(QMatrix4x4 const& point_de_vue, bool en_couleur = true);
  
  void dessineSphere(QMatrix4x4 const& point_de_vue,double rouge = 1.0, double vert = 1.0, double bleu = 1.0);
  void dessineSpherePos(double x, double y, double z,double rouge = 1.0, double vert = 1.0, double bleu = 1.0);
  
  void dessineRessort(QMatrix4x4 const& point_de_vue,Vecteur s1,Vecteur s2={0,0,0},unsigned int spires=6, int signe=1);                 
  void dessineHelice(QMatrix4x4 const& point_de_vue,double px, double py, double pz, double r,
																  double d, int nb_seg,double tours=1.0,int signe = 1);
  void dessineCercle(QMatrix4x4 const& point_de_vue,double px, double py, double pz, double r, int nb_seg,double c);
 
  void dessineTerrainPoints(QMatrix4x4 const& point_de_vue, std::string fichier_entree,
																				    double v_max=1.0, double range=1.0);
  void dessineTerrainMesh(QMatrix4x4 const& point_de_vue,std::vector<Vecteur> liste, 
																size_t lignes=70,double r=1.0, double v=1.0, double b=1.0);
  void dessineTriangle(QMatrix4x4 const& point_de_vue,Vecteur p1, Vecteur p2,Vecteur p3,
																				 double r=1.0, double v=1.0, double b=1.0);
  
  void dessinePales(QMatrix4x4 const& point_de_vue,double px, double py, double r, int n,int nb_seg);
  void dessineVentilo(QMatrix4x4 const& point_de_vue,double taille = 1.0, double dt=1);

 //======================================================================================================================== 
 private:
  double dt;
  // Un shader OpenGL encapsulé dans une classe Qt
  QOpenGLShaderProgram prog;
  GLSphere sphere;
  
  // Caméra
  QMatrix4x4 matrice_vue;

};

