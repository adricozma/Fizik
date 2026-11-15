#include <QApplication>
#include "glwidget.h"
#include "Erreur.h"
#include "ObjetMobile.h"
#include "Obstacle.h"
#include <QMatrix4x4>
int main(int argc, char* argv[])
{
  try{
  QApplication a(argc, argv);
  GLWidget w;
//=======================Comment créer un objet=========================
  //Balle/Caillou:
  // Balle(double masse, double rayon, double alpha, double mu, 
  //  const Vecteur& position, const Vecteur& vitesse);
//------------------------------------------------------------------------  
  //Boulet:
  // Boulet(double masse, double rayon, double alpha, double mu,
  //  Vecteur p, const Vecteur& p_ang, Vecteur v, 
  //  const Vecteur& v_ang);
//------------------------------------------------------------------------
  //Pendule:
    // Pendule(double massse, double rayon, double alpha, double mu, 
	//	double longueur, double b, const Vecteur& p, 
	//	const Vecteur& v, const Vecteur& O,
	//	const Vecteur& d);
//------------------------------------------------------------------------			
  //PeneduleSpherique:
	// PenduleSpherique(double masse, double rayon, double alpha, double mu,
	//	double longueur, const Vecteur& p, const Vecteur& v, const Vecteur& O,
	//	const Vecteur& d);
//------------------------------------------------------------------------	
  //Ressort:
	// Ressort(double masse, double rayon, double alpha, double mu, 
	//	const Vecteur& p, const Vecteur& v, const Vecteur& O,
	//	const Vecteur& d, double k, double b, double longeur_a_vide);
//------------------------------------------------------------------------  
  //PlanFini:
    // PlanFini(const Vecteur& origine, const Vecteur& longueur, 
    //const Vecteur& largeur, double alpha, double mu, bool couleur);
//------------------------------------------------------------------------  
  //PlanInfini:
    // PlanInfini(const Vecteur& Origine, const Vecteur& Normal, double alpha, double mu);
//------------------------------------------------------------------------
  //Brique:
    // Brique(const Vecteur& origine, const Vecteur& longueur, 
    //const Vecteur& largeur, double hauteur, double alpha, double mu);
//------------------------------------------------------------------------
  //Sphere:
    // Sphere(const Vecteur& position, double rayon, double alpha, double mu);
//------------------------------------------------------------------------
  //Terrain:
    //  Terrain(std::string f_d, std::string f_p, double scale, double t_x, double t_y, double t_z, 
    // double v_max, double range, double scaleZ,unsigned int div, std::vector<Vecteur> points_dessin);
//------------------------------------------------------------------------
  //ChampForces:
    //ChampForces(const Vecteur& intensite);
//------------------------------------------------------------------------
  //Vent
    // Vent(const Vecteur& origine, const Vecteur& longueur, 
    //const Vecteur& largeur, double profondeur, double V0);
//------------------------------------------------------------------------
  //Vetilateur:
    //Ventilateur(const Vent& V, double h_brique);
//------------------------------------------------------------------------
//La gravité pour tout le main()
	  double alpha(0.88); //coeff de restitution
	  double alpha1(1.05);
	  double mu(0.001);
	  ChampForces G(g);
	  w.ajoute(G);
	  
//==========================Situation 1=================================
	 //~ Balle B1(10,0.5,alpha1,mu, {1,1,8}, {0,0.5,0});
	 //~ Balle B2(10,0.5,alpha1,mu, {3,1,8}, {0,0.5,-0.5});
	 //~ Balle B3(10,0.5,alpha1,mu, {5,1,8}, {0,0,0});
	 //~ Balle B4(10,0.5,alpha1,mu, {2,2,8}, {-0.5,0.5,0});
	 //~ Balle B5(10,0.5,alpha1,mu, {4,3,8}, {0,0,0});
	 //~ w.ajoute(B1);
	 //~ w.ajoute(B2);
	 //~ w.ajoute(B3);
	 //~ w.ajoute(B4);
	 //~ w.ajoute(B5);	 
	 //~ Vecteur o({0,0,5});
	 //~ Vecteur l({8,0,0});
	 //~ Vecteur L({0,4,0});
	 
	 //~ Vecteur o1({0,2,5});
	 //~ Vecteur l1({17,0,0});
	 //~ Vecteur L1({0,12,0});
	 
	 //~ Brique B(o,L,l,5,alpha1, mu,false);
	 
	 //~ Ressort R(1, 0.2, alpha1,mu, {0.4}, {0.0}, {3,0,8},
			 //~ {sqrt(3)/3, sqrt(3)/3,-sqrt(3)/3}, 3, 0.01, 0.0);	 
	 //~ w.ajoute(R); 
	 
	 //~ w.ajoute(B);
//======================================================================
//==========================Situation 2=================================

//Se déplacer un peu pour chercher les montagnes

//~ Terrain K2("../height_data/HeightData_K2_xyz_decale_bis.txt",
	//~ "../height_data/HeightData_K2_xyz_decale_random.txt",0.01,0,0,0,-8000,2800,1.4,60);
Terrain K2("../height_data/HeightData_K2_xyz_decale_bis.txt",
	"../height_data/HeightData_K2_xyz_decale_bis.txt",0.01,0,0,0,-8000,2800,1,60);
//~ Terrain EV("../height_data/Height_Data_Everest_xyz_decale.txt",
	//~ "../height_data/Height_Data_Everest_xyz_decale.txt",0.01,-4000,-4000,-4000,8000,1500,1,70);
//~ Terrain CV("../height_data/HeightData_Cervin_xyz_decale.txt",
	//~ "../height_data/HeightData_Cervin_xyz_decale.txt",0.1,-6000,-4000,1500,4000,1500,1.2,40);
//~ Terrain GC("../height_data/HeightData_G-Canyon_xyz_decale_.txt",
	//~ "../height_data/HeightData_G-Canyon_random_xyz_decale_.txt",0.05,-1300,-1000,-1000,1350,300,7,70);
//~ Terrain GC("../height_data/HeightData_G-Canyon_xyz_decale_.txt",
//~ "../height_data/HeightData_G-Canyon_xyz_decale_.txt",0.05,-1300,-1000,-1000,1350,300,2,70);
	  //~ w.ajoute(GC);
	  //~ w.ajoute(K2); 
	  //~ w.ajoute(EV);

//~ Caillou c1(1,5,alpha,mu, {10,40,100}, {0,0,0});
	  //~ w.ajoute(c1);
//~ Caillou c2(1,5,alpha,mu, {22,40,100}, {0,0,0});
	  //~ w.ajoute(c2);
//~ Caillou c3(1,5,alpha,mu, {34,40,100}, {0,0,0});
	  //~ w.ajoute(c3);
//~ Caillou c4(1,5,alpha,mu, {46,40,100}, {0,0,0});
	  //~ w.ajoute(c4);
//~ Caillou c5(1,5,alpha,mu, {58,40,100}, {0,0,0});
	  //~ w.ajoute(c5);
//~ Caillou c6(1,5,alpha,mu, {10,52,100}, {0,0,0});
	  //~ w.ajoute(c6);
//~ Caillou c7(1,5,alpha,mu, {22,52,100}, {0,0,0});
	  //~ w.ajoute(c7);
//~ Caillou c8(1,5,alpha,mu, {34,52,100}, {0,0,0});
	  //~ w.ajoute(c8);
//~ Caillou c9(1,5,alpha,mu, {46,52,100}, {0,0,0});
	  //~ w.ajoute(c9);
//~ Caillou c10(1,5,alpha,mu, {58,52,100}, {0,0,0});
	  //~ w.ajoute(c10);
//======================================================================
//==========================Situation 3=================================

Caillou c11(10,1.5,alpha,mu, {20,0,52}, {0,0,0});
	  w.ajoute(c11);
Caillou c12(10,1.5,alpha,mu, {20,4,35}, {0,0,0});
	  w.ajoute(c12);
Caillou c13(10,1.5,alpha,mu, {20,8,35}, {0,0,0});
	  w.ajoute(c13);
Caillou c14(10,1.5,alpha,mu, {20,-3,35}, {0,0,0});
	  w.ajoute(c14);
Caillou c15(10,1.5,alpha,mu, {17,3,40}, {0,0,0});
	  w.ajoute(c15);
Caillou c16(10,1.5,alpha,mu, {20,9,50}, {0,0,0});
	  w.ajoute(c16);
	  	 
	 Vecteur v1_b1({-100,-100,-4});
	 Vecteur v1_b2({200,0,0});
	 Vecteur v1_b3({0,200,0});
	 PlanFini PF1(v1_b1, v1_b2, v1_b3);
	 w.ajoute(PF1);
	 
	 Vecteur v2_b1({20,-20,-2});
	 Vecteur v2_b2({0,40,0});
	 Vecteur v2_b3({40,0,40});
	 PlanFini PF2(v2_b1, v2_b3, v2_b2);
	 w.ajoute(PF2);
	 
	 Pendule P1(10.0, 1,alpha,mu, 7, 1.005, {3}, {0.0}, {1,1,8.81}, {1,-1,0});

	 w.ajoute(P1);
	 
	  Boulet boul(10,1.7,alpha,mu,{1,1,3},{1,0,0},{0,0,1},{0,2,0});
	  w.ajoute(boul);
	  
	  Ressort R(5, 1.5, alpha1,mu, {0.4}, {0.0}, {3,5,10},
			 {1, 0,0}, 1.5, 0.01, 0.0);	 
	 w.ajoute(R); 
	 
	 Sphere s({3,4,2},2,alpha,mu);
	 w.ajoute(s);
//======================================================================
//==========================Situation 4=================================
	 //~ Vecteur v3_b1({-100,-100,-4});
	 //~ Vecteur v3_b2({200,0,0});
	 //~ Vecteur v3_b3({0,200,0});
	 //~ PlanFini PF3(v3_b1, v3_b2, v3_b3,alpha, mu, false);
	 //~ w.ajoute(PF3);
	 
//~ Ressort R2(2, 0.2, alpha,mu, {0.4}, {0.0}, {0,0,4},
			 //~ {0, 1,-1}, 3, 0.01, 2);	 
	 //~ w.ajoute(R2); 
//~ Caillou c17(5,1.1,alpha,mu, {0,5,0}, {0,0,0});
	  //~ w.ajoute(c17);
	  
 //~ Vent G2({4,20,0},{-8,0,0},{0,0,2},2,3);
	  //~ Ventilateur v(G2,2);
	  //~ w.ajoute(v);
//======================================================================	



//====================================================================== 
  w.show();
  return a.exec();
}catch( Erreur e ){e.affiche(); return 1;} 
}
