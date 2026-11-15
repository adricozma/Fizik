
#include <cmath>
#include <vector>

#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include "ObjetMobile.h"
#include "Obstacle.h"
#include "ObjetCompose.h"
#include "Systeme.h"
#include "Vecteur.h"
#include "constantes.h"
using namespace std;
// ======================================================================
void VueOpenGL::dessine(Balle const& a_dessiner)
{
//Dessine deux fois les sphères, une fois en mode plein et une fois 
//en mode fil de fer(un tout petit peu plus grande. Question de style.

//----------------------mode: plein-------------------------------------
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  QMatrix4x4 matrice;
  matrice.translate(a_dessiner.getPosition().getVecteur()[0],
					a_dessiner.getPosition().getVecteur()[1],			
					a_dessiner.getPosition().getVecteur()[2]);
  matrice.scale(a_dessiner.getRayon()); //rayon de la balle
  dessineSphere(matrice, 1, 1,1); // blanc
  
//----------------------mode : fil de fer------------------------------- 
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
  matrice.setToIdentity();
  matrice.translate(a_dessiner.getPosition().getVecteur()[0],
					a_dessiner.getPosition().getVecteur()[1],			
					a_dessiner.getPosition().getVecteur()[2]);
  matrice.scale(a_dessiner.getRayon()*1.01);
  dessineSphere(matrice, 0.0, 0.0); // bleu
}
// ======================================================================
void VueOpenGL::dessine(Boulet const& a_dessiner){
	QMatrix4x4 matrice;
	Vecteur I1({1,0,0}); //repère orthonormé
    Vecteur I2({0,1,0}); 
    Vecteur I3({0,0,1});
    
	matrice.translate(	a_dessiner.getPosition().getVecteur()[0],
						a_dessiner.getPosition().getVecteur()[1],
						a_dessiner.getPosition().getVecteur()[2]);
	matrice.scale(a_dessiner.getRayon());
	
//On on oriente le repère de la sphère selon sa rotation propre
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	Vecteur v_xy((a_dessiner.getP_angulaire()*I1)*I1+(a_dessiner.getP_angulaire()*I2)*I2);
    double ang_z(acos((v_xy*I1)/(v_xy.norme()))*180/M_PI);
    
    double ang_y_p(acos((a_dessiner.getV_angulaire()*I3)/(a_dessiner.getV_angulaire().norme()))*180/M_PI);
    matrice.rotate(ang_z,0,0,1);
	matrice.rotate(ang_y_p,0,1,0);
	
	dessineSphere(matrice,1,0,0);
	
}
// ======================================================================
void VueOpenGL::dessine(Ressort const& a_dessiner)
{	
	Vecteur I1({1,0,0});
    Vecteur I2({0,1,0}); 
    Vecteur I3({0,0,1});
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	QMatrix4x4 matrice;
	matrice.translate(	a_dessiner.getPosition().getVecteur()[0],
						a_dessiner.getPosition().getVecteur()[1],			
						a_dessiner.getPosition().getVecteur()[2]);
					
	matrice.scale(a_dessiner.getRayon());
	dessineSphere(matrice, 1.0,0.0,0.0);
    
    //~ Calcul de l'angle que fait le ressort dans le repère
    //~ On fait une translation pour placer l'origine du repère au point d'attache du ressort
	//~ on oriente l'axe de z sur le vecteur direction du ressort car le ressort se dessine
	//~ toujours selon l'axe z
    
    //rotation autour de z
    Vecteur v_xy((a_dessiner.getDirection()*I1)*I1+(a_dessiner.getDirection()*I2)*I2);
    double ang_z(acos((v_xy*I1)/(v_xy.norme()))*180/M_PI);
    //rotation autour de y'
    double ang_y_p(acos((a_dessiner.getDirection()*I3)/(a_dessiner.getDirection().norme()))*180/M_PI);
    
    Vecteur o({0,0,0});
    unsigned int spires(6); //por le nombre de spires du ressort
    
	matrice.setToIdentity();
	matrice.translate(a_dessiner.getAttache()*I1,a_dessiner.getAttache()*I2,a_dessiner.getAttache()*I3);
	matrice.rotate(ang_z,0,0,1);
	matrice.rotate(ang_y_p,0,1,0);

//gère le dessin du ressort car son orientation change selon son vecteur direction
	//~ if((a_dessiner.getAttache()*I3-a_dessiner.getPosition()*I3)<0.0){	
		//~ dessineRessort(matrice, o, a_dessiner.getPosition()-a_dessiner.getAttache(),spires,-1);
	//~ }else{
		dessineRessort(matrice, o, a_dessiner.getPosition()-a_dessiner.getAttache(),spires,1);
	//~ }
	
}
// ======================================================================
void VueOpenGL::dessine(PlanFini const& a_dessiner)
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //mode plein
  QMatrix4x4 matrice;
  
  if(a_dessiner.getCouleur()){
	dessinePlanfini(matrice, a_dessiner.getPosition(),a_dessiner.getLongueur(), a_dessiner.getLargeur());
	dessineAxes(matrice);
  }
}
// ======================================================================
void VueOpenGL::dessine(PlanInfini const& a_dessiner)
{
//On ne dessine pas de plans infini car cela reviendrait a dessiner un plan
// fini très grand
}
// ======================================================================
void VueOpenGL::dessine(Systeme const& a_dessiner)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //efface l'ecran avant l'affichage de du systeme
  for(const auto& dessin: a_dessiner.getListeDessins()){
	dessin->dessine_sur(*this);
  } 
}   

// ======================================================================
void VueOpenGL::dessine(Pendule const& a_dessiner)
{
	//mode "fil de fer pour le differentier des balles"
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
	
	QMatrix4x4 matrice;
	//Point d'attache du pendule
	Vecteur attache(a_dessiner.getOrigine());
	prog.setUniformValue("vue_modele", matrice_vue * matrice);
	
	//On dessine l'axe du pendule (ligne)
	glBegin(GL_LINES);
	prog.setAttributeValue(SommetId, 	a_dessiner.getPosition().getVecteur()[0],
										a_dessiner.getPosition().getVecteur()[1],
										a_dessiner.getPosition().getVecteur()[2]+
										a_dessiner.getRayon());
										
	prog.setAttributeValue(SommetId, 	attache.getVecteur()[0],
										attache.getVecteur()[1],
										attache.getVecteur()[2]);
	glEnd();
	
	matrice.translate(	a_dessiner.getPosition().getVecteur()[0],
						a_dessiner.getPosition().getVecteur()[1],			
						a_dessiner.getPosition().getVecteur()[2]);
	
	//attribut rayon du pendule
    matrice.scale(a_dessiner.getRayon()); 
    
    dessineSphere(matrice,0,1,0);//vert
}
// ======================================================================
void VueOpenGL::dessine(PenduleSpherique const& a_dessiner)
//Ressemble beaucoup à dessine Penedule classique, mais cela est du au fait 
//Qu'il est plus simple d'éviter de faire une transformation et de 
//dessinner directement au point ou on veut dessiner
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	QMatrix4x4 matrice;
	//Repère cartésien
	Vecteur I1({1,0,0});
	Vecteur I2({0,1,0});
	Vecteur I3({0,0,1});
	//Point d'attache du pendule
	Vecteur attache(a_dessiner.getOrigine());
	prog.setUniformValue("vue_modele", matrice_vue * matrice);
	
	//On dessine l'axe du pendule
	glBegin(GL_LINES);
	prog.setAttributeValue(SommetId,	a_dessiner.getPosition().getVecteur()[0],
										a_dessiner.getPosition().getVecteur()[1],
										a_dessiner.getPosition().getVecteur()[2]
										+a_dessiner.getRayon());
	
	prog.setAttributeValue(SommetId, 	a_dessiner.getPosition().getVecteur()[0],
										a_dessiner.getPosition().getVecteur()[1],
										a_dessiner.getPosition().getVecteur()[2]+
										a_dessiner.getRayon());
	glEnd();
	
	matrice.translate(	a_dessiner.getPosition().getVecteur()[0],
						a_dessiner.getPosition().getVecteur()[1],			
						a_dessiner.getPosition().getVecteur()[2]);
	
	//attribut rayon du pendule
    matrice.scale(a_dessiner.getRayon()); 
    
    dessineSphere(matrice,0,0,1);//bleu
}
// ======================================================================
void VueOpenGL::dessine(Brique const& a_dessiner)
{
	Vecteur I1({1,0,0});
    Vecteur I2({0,1,0}); 
    Vecteur I3({0,0,1});
    
	if(a_dessiner.getCouleur()){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
	//On dessine un cube au centre de la brique
	QMatrix4x4 matrice;
	matrice.translate(	(a_dessiner.getPosition()+0.5*a_dessiner.getLongueur()+
						0.5*a_dessiner.getLargeur()-(a_dessiner.getNormal()*a_dessiner.getHauteur())*0.5).getVecteur()[0],
						(a_dessiner.getPosition()+0.5*a_dessiner.getLongueur()+
						0.5*a_dessiner.getLargeur()-(a_dessiner.getNormal()*a_dessiner.getHauteur())*0.5).getVecteur()[1],			
						(a_dessiner.getPosition()+0.5*a_dessiner.getLongueur()+
						0.5*a_dessiner.getLargeur()-(a_dessiner.getNormal()*a_dessiner.getHauteur())*0.5).getVecteur()[2]);
	
	//On oriente les faces du cube correctement					
	Vecteur v_xy((a_dessiner.getLongueur()*I1)*I1+(a_dessiner.getLongueur()*I2)*I2);
    double ang_z(acos((v_xy*I1)/(v_xy.norme()))*180/M_PI);
    
    double ang_y_p(acos((a_dessiner.getNormal()*I3)/(a_dessiner.getNormal().norme()))*180/M_PI);
    matrice.rotate(ang_z,0,0,1);
	matrice.rotate(ang_y_p,0,1,0);
	//On lui donne la bonne taille
	matrice.scale(a_dessiner.getLongueur().norme()*0.5,a_dessiner.getLargeur().norme()*0.5,a_dessiner.getHauteur()*0.5);					
	
	//Finalement on peut le dessiner dans le bon repère
	dessineCube(matrice);
	//dessineBrique(matrice, a_dessiner.getPosition(), a_dessiner.getLongueur(),
	//a_dessiner.getLargeur(),a_dessiner.getNormal(),a_dessiner.getHauteur(),0.3,0.3,0.3);
}
//================================================================================
void VueOpenGL::dessine(Sphere const& a_dessiner){
	Vecteur I1({1,0,0});
	Vecteur I2({0,1,0});
	Vecteur I3({0,0,1});
	
	QMatrix4x4 matrice;
	matrice.translate(	a_dessiner.getPosition().getVecteur()[0],
						a_dessiner.getPosition().getVecteur()[1],			
						a_dessiner.getPosition().getVecteur()[2]);
						
	matrice.scale(a_dessiner.getRayon());
	dessineSphere(matrice, 1,1,0);
}
//================================================================================
void VueOpenGL::dessine(Terrain const& a_dessiner){
//Globalement il y a deux façons de dessiner le terrain soit en "mesh" triangulaire
//Soit sous forme de cercles qui representent chaque point

//-------------------------------Cercles--------------------------------
	//~ QMatrix4x4 matrice1;
	//~ //Utile seulement pour le dessin du terrain en mode points
	//~ matrice1.scale(a_dessiner.getScale(),a_dessiner.getScale(),a_dessiner.getScaleZ()*a_dessiner.getScale());
    //~ matrice1.translate(a_dessiner.getTransX(),a_dessiner.getTransY(),a_dessiner.getTransZ());
    //~ glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//~ dessineTerrainPoints(matrice1,a_dessiner.getDessin(),a_dessiner.getVmax(),a_dessiner.getRange());
//---------------------------------Mesh--------------------------------	
	QMatrix4x4 matrice2;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // passe en mode "fil de fer"
	dessineTerrainMesh(matrice2,a_dessiner.getPointsDessin(),a_dessiner.getDivision(),1,1,1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//dessineTerrainMesh(matrice2,a_dessiner.getPointsDessin(),a_dessiner.getDivision(),0.3765,0.3765,0.3765);
	dessineTerrainMesh(matrice2,a_dessiner.getPointsDessin(),a_dessiner.getDivision(),0,0,0);
}
//================================================================================
void VueOpenGL::dessine(Ventilateur const& a_dessiner){
	
	Vecteur I1({1,0,0});
	Vecteur I2({0,1,0});
	Vecteur I3({0,0,1});
	
	QMatrix4x4 matrice;
					
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	
	dessine(a_dessiner.getBrique());
	matrice.setToIdentity();
	
//on veut se placer au centre de la face de la brique pour dessiner la pales
		matrice.translate(	    (a_dessiner.getBrique().getPosition()+0.5*a_dessiner.getBrique().getLongueur()+
								0.5*a_dessiner.getBrique().getLargeur()).getVecteur()[0],
								(a_dessiner.getBrique().getPosition()+0.5*a_dessiner.getBrique().getLongueur()+
								0.5*a_dessiner.getBrique().getLargeur()).getVecteur()[1],			
								(a_dessiner.getBrique().getPosition()+0.5*a_dessiner.getBrique().getLongueur()+
								0.5*a_dessiner.getBrique().getLargeur()).getVecteur()[2]);
								
//On oriente correctement notre repère pour être dans le sens du vent
	Vecteur normal(a_dessiner.getBrique().getNormal());
	Vecteur v_xy((normal*I1)*I1+(normal*I2)*I2);
    double ang_z(acos((v_xy*I1)/(v_xy.norme()))*180/M_PI);
    double ang_y_p((acos(normal*I3)/normal.norme())*180/M_PI);
	matrice.rotate(ang_z,0,0,1);
	matrice.rotate(ang_y_p,0,1,0);
//OOn dessine les pales												
	double taille (a_dessiner.getBrique().getLargeur().norme()/4.0);
	dessineVentilo(matrice,taille,100*dt);
}
//================================================================================
void VueOpenGL::init()
{
  /* Initialise notre vue OpenGL.
   * Dans cet exemple, nous créons et activons notre shader.
   *
   * En raison du contenu des fichiers *.glsl, le shader de cet exemple
   * NE permet QUE de dessiner des primitives colorées
   * (pas de textures, brouillard, reflets de la lumière ou autres).
   *
   * Il est séparé en deux parties VERTEX et FRAGMENT.
   * Le VERTEX :
   * - récupère pour chaque sommet des primitives de couleur (dans
   *     l'attribut couleur) et de position (dans l'attribut sommet)
   * - multiplie l'attribut sommet par les matrices 'vue_modele' et
   *     'projection' et donne le résultat à OpenGL
   *   - passe la couleur au shader FRAGMENT.
   *
   * Le FRAGMENT :
   *   - applique la couleur qu'on lui donne
   */

  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

  /* Identifie les deux attributs du shader de cet exemple
   * (voir vertex_shader.glsl).
   *
   * L'attribut identifié par 0 est particulier, il permet d'envoyer un
   * nouveau "point" à OpenGL
   *
   * C'est pourquoi il devra obligatoirement être spécifié et en dernier
   * (après la couleur dans cet exemple, voir plus bas).
   */

  prog.bindAttributeLocation("sommet",  SommetId);
  prog.bindAttributeLocation("couleur", CouleurId);

  // Activation du shader
  prog.bind();

  /* Activation du "Test de profondeur" et du "Back-face culling"
   * Le Test de profondeur permet de dessiner un objet à l'arrière-plan
   * partielement caché par d'autres objets.
   *
   * Le Back-face culling consiste à ne dessiner que les face avec ordre
   * de déclaration dans le sens trigonométrique.
   */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  sphere.initialize();                                      // initialise la sphère
  initializePosition();
}

// ======================================================================
void VueOpenGL::initializePosition()
{
  // position initiale
  matrice_vue.setToIdentity();
  matrice_vue.rotate(-50.0, 1.0, 0.0, 0.0);
  matrice_vue.translate(0.0,10.0, -10.0);
}

// ======================================================================
void VueOpenGL::translate(double x, double y, double z)
{
  /* Multiplie la matrice de vue par LA GAUCHE.
   * Cela fait en sorte que la dernière modification apportée
   * à la matrice soit appliquée en dernier (composition de fonctions).
   */
  QMatrix4x4 translation_supplementaire;
  translation_supplementaire.translate(x, y, z);
  matrice_vue = translation_supplementaire * matrice_vue;

}

// ======================================================================

void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z)
{
  // Multiplie la matrice de vue par LA GAUCHE
  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  matrice_vue = rotation_supplementaire * matrice_vue;
  
}
// ======================================================================
void VueOpenGL::dessineBrique(QMatrix4x4 const& point_de_vue,Vecteur o,Vecteur L,Vecteur l,Vecteur n,double h, double r, double v,  double b){
//Cette méthode ne fonctionne pas bien pour l'instant c'est pour cela qu'on utilise dessineCubube()
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  //Vecteur n((~(L^l))*h);
  n*=h;
  
  //Face du haut
  double s1_x(o.getVecteur()[0]); 		 double s1_y(o.getVecteur()[1]);		double s1_z(o.getVecteur()[2]);
  double s2_x((o+L).getVecteur()[0]); 	 double s2_y((o+L).getVecteur()[1]); 	double s2_z((o+L).getVecteur()[2]);
  double s3_x((o+L+l).getVecteur()[0]);  double s3_y((o+L+l).getVecteur()[1]); 	double s3_z((o+L+l).getVecteur()[2]);
  double s4_x((o+l).getVecteur()[0]); 	 double s4_y((o+l).getVecteur()[1]); 	double s4_z((o+l).getVecteur()[2]);
  //face du bas
  double s5_x((o-n).getVecteur()[0]); 	 double s5_y((o-n).getVecteur()[1]); 	double s5_z((o-n).getVecteur()[2]);
  double s6_x((o-n+L).getVecteur()[0]);  double s6_y((o-n+L).getVecteur()[1]); 	double s6_z((o-n+L).getVecteur()[2]);
  double s7_x((o-n+L+l).getVecteur()[0]);double s7_y((o-n+L+l).getVecteur()[1]);double s7_z((o-n+L+l).getVecteur()[2]);
  double s8_x((o-n+l).getVecteur()[0]);  double s8_y((o-n+l).getVecteur()[1]);	double s8_z((o-n+l).getVecteur()[2]);
  
  dessineSpherePos(s1_x,s1_y,s1_z);
  dessineSpherePos(s2_x,s2_y,s2_z);
  dessineSpherePos(s3_x,s3_y,s3_z);
  dessineSpherePos(s4_x,s4_y,s4_z);
  
  dessineSpherePos(s5_x,s5_y,s5_z);
  dessineSpherePos(s6_x,s6_y,s6_z);
  dessineSpherePos(s7_x,s7_y,s7_z);
  dessineSpherePos(s8_x,s8_y,s8_z);
  
//L'ordre des points change pour orienter les faces ainsi 
//elles sont visibles de notre point de vue 

  glBegin(GL_QUADS);
  //face du haut
  prog.setAttributeValue(CouleurId, r, v, b);
  prog.setAttributeValue(SommetId, s1_x, s1_y, s1_z);
  prog.setAttributeValue(SommetId, s2_x, s2_y, s2_z);
  prog.setAttributeValue(SommetId, s3_x, s3_y, s3_z);
  prog.setAttributeValue(SommetId, s4_x, s4_y, s4_z);
  glEnd();
  
  glBegin(GL_QUADS);	
  //face du bas
  prog.setAttributeValue(CouleurId, r, v, b); 
  prog.setAttributeValue(SommetId, s5_x, s5_y, s5_z);
  prog.setAttributeValue(SommetId, s8_x, s8_y, s8_z);
  prog.setAttributeValue(SommetId, s7_x, s7_y, s7_z);
  prog.setAttributeValue(SommetId, s6_x, s6_y, s6_z);

  glEnd();
  glBegin(GL_QUADS);
  //face derrière
  prog.setAttributeValue(CouleurId, r, v, b); 
  prog.setAttributeValue(SommetId, s5_x, s5_y, s5_z);
  prog.setAttributeValue(SommetId, s6_x, s6_y, s6_z);
  prog.setAttributeValue(SommetId, s2_x, s2_y, s2_z);
  prog.setAttributeValue(SommetId, s1_x, s1_y, s1_z);

  glEnd();
  glBegin(GL_QUADS);
  // face devant
  prog.setAttributeValue(CouleurId, r, v, b); 
  prog.setAttributeValue(SommetId, s8_x, s8_y, s8_z);
  prog.setAttributeValue(SommetId, s4_x, s4_y, s4_z);
  prog.setAttributeValue(SommetId, s3_x, s3_y, s3_z);
  prog.setAttributeValue(SommetId, s7_x, s7_y, s7_z);

  glEnd();
  glBegin(GL_QUADS);
  // face droite
  prog.setAttributeValue(CouleurId, r, v, b); 
  prog.setAttributeValue(SommetId, s6_x, s6_y, s6_z);
  prog.setAttributeValue(SommetId, s7_x, s7_y, s7_z);
  prog.setAttributeValue(SommetId, s3_x, s3_y, s3_z);
  prog.setAttributeValue(SommetId, s2_x, s2_y, s2_z);
  
  glEnd();
  glBegin(GL_QUADS);
  // face gauche
  prog.setAttributeValue(CouleurId, r, v, b); 
  prog.setAttributeValue(SommetId, s5_x, s5_y, s5_z);
  prog.setAttributeValue(SommetId, s1_x, s1_y, s1_z);
  prog.setAttributeValue(SommetId, s4_x, s4_y, s4_z);
  prog.setAttributeValue(SommetId, s8_x, s8_y, s8_z);

  glEnd();
}
// ======================================================================
void VueOpenGL::dessineCube (QMatrix4x4 const& point_de_vue, double r, double v,  double b)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_QUADS);
  // face coté X = +1
  prog.setAttributeValue(CouleurId, r, v, b); 
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

  // face coté X = -1
  prog.setAttributeValue(CouleurId, r, v, b); 
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

  // face coté Y = +1
  prog.setAttributeValue(CouleurId, r, v, b); 
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

  // face coté Y = -1
  prog.setAttributeValue(CouleurId, r, v, b); // cyan
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

  // face coté Z = +1
  prog.setAttributeValue(CouleurId, r, v, b); 
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

  // face coté Z = -1
  prog.setAttributeValue(CouleurId, r, v, b); 
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  glEnd();
}
// ======================================================================
void VueOpenGL::dessinePlanfini(QMatrix4x4 const& point_de_vue,Vecteur o, Vecteur L, Vecteur l)
{
	prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
	
	Vecteur I1({1,0,0});
    Vecteur I2({0,1,0});
    Vecteur I3({0,0,1});
  
	double s1_x(o*I1); 		double s1_y(o*I2);		double s1_z(o*I3);
	double s2_x((o+L)*I1); 	double s2_y((o+L)*I2); 	double s2_z((o+L)*I3);
	double s3_x((o+L+l)*I1);double s3_y((o+L+l)*I2);double s3_z((o+L+l)*I3);
	double s4_x((o+l)*I1); 	double s4_y((o+l)*I2); 	double s4_z((o+l)*I3);
  
	glBegin(GL_QUADS);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	prog.setAttributeValue(CouleurId, 0.5, 1, 0.7); 
	prog.setAttributeValue(SommetId, s1_x, s1_y, s1_z);
	prog.setAttributeValue(SommetId, s2_x, s2_y, s2_z);
	prog.setAttributeValue(SommetId, s3_x, s3_y, s3_z);
	prog.setAttributeValue(SommetId, s4_x, s4_y, s4_z);
	  
	glEnd();
}
// ======================================================================
void VueOpenGL::dessineSphere (QMatrix4x4 const& point_de_vue,
                               double rouge, double vert, double bleu)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  prog.setAttributeValue(CouleurId, rouge, vert, bleu);  // met la couleur
  sphere.draw(prog, SommetId);                           // dessine la sphère
}
// ======================================================================
void VueOpenGL::dessineAxes(QMatrix4x4 const& point_de_vue, bool en_couleur)
{
  glBegin(GL_LINES);
 
  // axe X
  if (en_couleur) {
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  } else {
    prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); // blanc
  }    
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 1.0, 0.0, 0.0);
 
  // axe Y
  if (en_couleur) prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 1.0, 0.0);
 
  // axe Z
  if (en_couleur) prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 0.0, 1.0);
 
  glEnd();
}
// ======================================================================
void VueOpenGL::dessineRessort(QMatrix4x4 const& point_de_vue,Vecteur s1,Vecteur s2,unsigned int spires, int signe)
{	
	prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
	Vecteur V1({1,0,0});
	Vecteur V2({0,1,0});
	Vecteur V3({0,0,1});
//Le ressort se dessine puis après se retrouve translaté
//Alors on peut utiliser un repère orthonormé standard ici
	double h_res((s2-s1).norme());
	dessineHelice(point_de_vue, s1*V1, s1*V2, s1*V3,0.2,h_res,100,spires,signe);
}
// ======================================================================
void VueOpenGL::dessineHelice(QMatrix4x4 const& point_de_vue,double px, double py, double pz, 
																double r,double d, int nb_seg, double tours, int signe)
{	
	prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
	glBegin(GL_LINE_LOOP);
		for(int i(0); i<=nb_seg; ++i){
			if(i<nb_seg){
//On peut décider le nombre d'hélices que le ressort possède (tours)
				double phi(tours*2*M_PI*i/nb_seg);
				double x = r*cos(phi);
				double y = r*sin(phi);
				double z=  i*d/nb_seg;
				glVertex3d(px+x, py+y, pz+(signe*z));
//Par convention on dessine le ressort vers le bas "pz+z" (vers le haut)
			}
	        
		}
	glEnd();
}
// ======================================================================
void VueOpenGL::dessineCercle(QMatrix4x4 const& point_de_vue,double px, double py, double pz, 
																double r, int nb_seg, double c)
{
	prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
	glBegin(GL_POLYGON);
	prog.setAttributeValue(CouleurId, 1-c,c,1*1/c);
		for(int i(0); i<=nb_seg; ++i){
			if(i<nb_seg){
				double phi(2*M_PI*i/nb_seg);
				double x = r*cos(phi);
				double y = r*sin(phi);
				glVertex3d(x+px, y+py, pz);
			}
		}
	glEnd();
}
// ======================================================================
void VueOpenGL::dessineTerrainPoints(QMatrix4x4 const& point_de_vue, std::string fichier_entree, double v_max, double range){
//dessine un cercle en chaque point, orienté vers le haut (axe z)	
	prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
	
	ifstream entree(fichier_entree);
	QMatrix4x4 matrice;
	matrice=point_de_vue;
	if(!(entree.fail())){
		std::string element1;
		std::string element2;
		std::string element3;
		while(entree>>element1>>element2>>element3){
			if(!(entree.eof())){
				double x(stod(element1)); double y(stod(element2)); double z(stod(element3));
				dessineCercle(matrice, x,y,z,45,5,(v_max-z)/range);
			}
		}
		entree.close();

	}else{
		std::cerr<<" Impossible d'ouvrir les fichiers"<<endl;
	}	
}
// ======================================================================
void VueOpenGL::dessineTerrainMesh(QMatrix4x4 const& point_de_vue, const vector<Vecteur>& liste, size_t lignes, double r, double v, double b){
// [PERF] Remplacement de ~9500 appels glBegin/glEnd + cout par un VBO GPU unique (QOpenGLBuffer)
	if (lignes < 2 || liste.empty()) return;

	if (!terrain_vbo_ready) {
		QVector<GLfloat> vertices;
		vertices.reserve(static_cast<int>(18 * (lignes - 1) * (lignes - 1)));
		Vecteur I1({1,0,0}), I2({0,1,0}), I3({0,0,1});
		auto push_v = [&vertices, &I1, &I2, &I3](const Vecteur& p) {
			vertices << static_cast<GLfloat>(p * I1)
			         << static_cast<GLfloat>(p * I2)
			         << static_cast<GLfloat>(p * I3);
		};
		for (size_t n = 0; n < lignes - 1; ++n) {
			for (size_t i = 0; i < lignes - 1; ++i) {
				const Vecteur& a = liste[i + n * lignes];
				const Vecteur& c = liste[i + n * lignes + 1];
				const Vecteur& d = liste[i + (n + 1) * lignes];
				const Vecteur& e = liste[i + (n + 1) * lignes + 1];
				push_v(a); push_v(c); push_v(d);
				push_v(c + epsilon); push_v(e + epsilon); push_v(d + epsilon);
			}
		}
		terrain_vertex_count = vertices.size() / 3;
		terrain_vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
		terrain_vbo.create();
		terrain_vbo.bind();
		terrain_vbo.allocate(vertices.constData(), vertices.size() * static_cast<int>(sizeof(GLfloat)));
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
}
// ======================================================================
void VueOpenGL::dessineTriangle(QMatrix4x4 const& point_de_vue,Vecteur p1, Vecteur p2, Vecteur p3,double r, double v, double b){
	Vecteur I1({1,0,0});
	Vecteur I2({0,1,0});
	Vecteur I3({0,0,1});
	
	prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
	glBegin(GL_TRIANGLES);
	
	 prog.setAttributeValue(CouleurId, r,v,b);
	 prog.setAttributeValue(SommetId, p1*I1,p1*I2,p1*I3);
	 prog.setAttributeValue(SommetId, p2*I1,p2*I2,p2*I3);
	 prog.setAttributeValue(SommetId, p3*I1,p3*I2,p3*I3);
	glEnd();
}
// ======================================================================
void VueOpenGL::dessinePales(QMatrix4x4 const& point_de_vue,double px, double py, double r, int n, int nb_seg){
//Dessine simplement une équation qui fait des boucles
	prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
	glBegin(GL_POLYGON);
	prog.setAttributeValue(CouleurId, 1,0,0);
		for(int i(0); i<=nb_seg; ++i){
			if(i<nb_seg){
				double phi((2*M_PI*i)/nb_seg);
				double x = cos(phi*n)*sin(phi);
				double y = cos(phi*n)*cos(phi);
				prog.setAttributeValue(SommetId, x, y, 1);
			}
		}
	glEnd();
}
// ======================================================================
void VueOpenGL::dessineVentilo(QMatrix4x4 const& point_de_vue,double taille,double dt){
//dessine la sphère et les pales qui reposent dessus ppppourr simuler le ventialteur 
	prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
	QMatrix4x4 matrice=point_de_vue;
	
	matrice.scale(taille);
	dessineSphere(matrice);
	
   
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	matrice=point_de_vue;
	matrice.translate(0,0,-taille);
	matrice.scale(2*taille);
	matrice.rotate(dt,0,0,1);
	dessinePales(matrice,0,0,0,4,100);
}
// ======================================================================
void VueOpenGL::dessineSpherePos(double x, double y, double z,double rouge, double vert, double bleu){
//Fonction outil pour dessiner une sphère en des points x,y,z au lieu de la 
//deplacer à laide de transformations
	QMatrix4x4 matrice;
	matrice.translate(x,y,z);
	dessineSphere(matrice,rouge,vert,bleu);
}
