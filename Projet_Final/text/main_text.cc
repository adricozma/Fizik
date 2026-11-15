#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "support_a_dessin.h"
#include "ChampForces.h"
#include "constantes.h"
#include "ObjetMobile.h"
#include "Obstacle.h"
#include "Systeme.h"
#include "Integrateur.h"
#include "ObjetCompose.h"
#include "Vecteur.h"
using namespace std;

void Simule(Systeme& S, SupportADessin& D, Integrateur& I, unsigned int nb, double dt = 0.01){
	while(nb > 0){
		S.evolue(I,1,dt);
		S.dessine_sur(D);
		--nb;
	}
}
int main()
{try{
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

	ofstream sortie("gnuplot/Fichier_sortie.txt");
	double alpha(0.88);
	double mu(1.02);
	//sortie pour un fichier texte, cout sinon
	TextViewer ecran(sortie);
	Systeme S;
	ChampForces G(g);
	G.ajoute(S);
//==========================Situation 1=================================
	 //~ Balle B1(10,0.5,alpha,mu, {1,1,8}, {0,0.5,0});
	 //~ Balle B2(10,0.5,alpha,mu, {3,1,8}, {0,0.5,-0.5});
	 //~ Balle B3(10,0.5,alpha,mu, {5,1,8}, {0,0,0});
	 //~ Balle B4(10,0.5,alpha,mu, {2,2,8}, {-0.5,0.5,0});
	 //~ Balle B5(10,0.5,alpha,mu, {4,3,8}, {0,0,0});
	 //~ B1.ajoute(S);
	 //~ B2.ajoute(S);
	 //~ B3.ajoute(S);
	 //~ B4.ajoute(S);
	 //~ B5.ajoute(S);	 
	 //~ Vecteur o({0,0,5});
	 //~ Vecteur l({8,0,0});
	 //~ Vecteur L({0,4,0});
	 
	 //~ Vecteur o1({0,2,5});
	 //~ Vecteur l1({17,0,0});
	 //~ Vecteur L1({0,12,0});
	 
	 //~ Brique Br(o,L,l,5,alpha, mu,false);
	 //~ Br.ajoute(S);
	 
	 //~ Ressort R(1, 0.2, alpha,mu, {0.4}, {0.0}, {3,0,8},
			 //~ {sqrt(3)/3, sqrt(3)/3,-sqrt(3)/3}, 3, 0.01, 0.0);	 
	 //~ R.ajoute(S);
	 
//======================================================================
//==========================Situation 2=================================

Caillou c12(10,1.5,alpha,mu, {20,4,35}, {0,0,0});
	  c12.ajoute(S);
Caillou c13(10,1.5,alpha,mu, {20,8,35}, {0,0,0});
	  c13.ajoute(S);
Caillou c14(10,1.5,alpha,mu, {20,-3,35}, {0,0,0});
	  c14.ajoute(S);
Caillou c15(10,1.5,alpha,mu, {17,3,40}, {0,0,0});
	  c15.ajoute(S);
Caillou c16(10,1.5,alpha,mu, {20,9,50}, {0,0,0});
	  c16.ajoute(S);
	  	 
	 Vecteur v1_b1({-100,-100,-4});
	 Vecteur v1_b2({200,0,0});
	 Vecteur v1_b3({0,200,0});
	 PlanFini PF1(v1_b1, v1_b2, v1_b3);
	 PF1.ajoute(S);
	 
	 Vecteur v2_b1({20,-20,-2});
	 Vecteur v2_b2({0,40,0});
	 Vecteur v2_b3({40,0,40});
	 PlanFini PF2(v2_b1, v2_b3, v2_b2);
	 PF2.ajoute(S);
	 
	 Pendule P1(10.0, 1,alpha,mu, 7, 1.005, {3}, {0.0}, {1,1,8.81}, {1,-1,0});

	 P1.ajoute(S);

	  Vent G3({-40,-20,80},{10,0,-100},{0,100,0},50,10);
	  Ventilateur v(G3,3);
	    v.ajoute(S);
	  //~ Boulet boul(10,1.7,alpha,mu,{1,1,3},{1,0,0},{0,0,1},{0,2,0});
	  //~ boul.ajoute(S);
//======================================================================
	double dt(1.0/1000.0);
	unsigned int nb(10000); //Nombre d'itérations
	Integrateur I1;
	IntegrateurEulerCromer I2;
	IntegrateurRungeKutta I3;
	Simule(S,ecran,I3, nb, dt);
	//~ for(int i(1); i<=nb; ++i){
		//~ S.evolue(I3,1,dt);
		//~ S.dessine_sur(ecran);
	//~ }
	return 0;
}catch(Erreur E){E.affiche();return 1;}
}
