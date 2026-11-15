#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "Systeme.h"
#include "Erreur.h"
#include "ObjetCompose.h"

using namespace std;


int main()
{
try{
	double M_V(3), R(0.051111), M(M_V * (4.0/3.0 * M_PI * R*R*R));
	double mv(3.0), r(0.2), m(mv * 4.0/3.0 * M_PI * r * r *r);
	ChampForces c(g);
	//~ Balle B0(0,1, {0,0,0}, {0,0,0});
	Balle B1(M, R, 0.8, 0.00, {0,1.36675,0.283821}, {0,0.715449,0.0957368});
	Balle BT(M, R, 0.8, 0.00, {0,0,0.3}, {0,0.8,2});
	Balle B2(0.1, 0.05, 0.8, 0.00, {0,1.46284,0.260128}, {0,0.419218,0.13874});
	Pendule P1(0.1, 0.05, 0.8, 0.00, 0.2, 0.005, {0.0}, {20.0}, {0,1.4,0.45},{0,1,0});
	Pendule P2(1.0, 0.1, 0.8, 0.00, 0.2, 0.005, {0.0}, {0.0}, {0,0,0.31}, {0,1,0});
	Pendule P3(1.0, 0.1, 0.8, 0.00, 0.9, 0.005, {1.0}, {0.0}, {0,0,1.01}, {0,1,0});
	Pendule PT(0.1, 0.05, 0.8, 0.00, 0.2, 0.005, {1.5}, {-0.5}, {0,1.4, 0.45}, {0,1,0});
	Pendule P4(m,r, 0.8, 0.00, 2.0, 0.005, {0}, {0}, {0,0,2}, {0,1,0});
	Pendule P5(m,r,0.8, 0.00, 2.0, 0.005, {1}, {0}, {0,0,2}, {0,1,0});
	Balle B3(M, R, 0.8, 0.00, {0,0.624,0.0465234}, {0,0.8,-2.59108});
	Balle B4(M, R, 0.8, 0.00, {0,2,1}, {1,1,0});
	Balle B5(1.0, 1.0, 0.8, 0.00, {1,1,1}, {1,5,0});
	Balle B6(3.0, 0.1, 0.8, 0.00, {0.5,0.5,0.1}, {-20.0,-20.0,0});
	Balle B7(0.1, 0.05, 0.8, 0.00, {0,0.2,5}, {0,-0.2,0});							//B7 et B8 servent à tester le "roulement" sur les plans 
	Balle B8(10.0, 1.0, 0.8, 0.00, {0,0,5}, {-0.5, -0.5, 0});
	Balle B9(1.0, 0.1, 0.8, 0.00, {0.5,0.5,1.5}, {0.1, 0.1, -1});
	Balle B10(1.0, 0.1, 0.8, 0.00, {0,0,1}, {-1,-1,-1});
	Caillou C1(1.0, 0.1, 0.8, 0.00, {0.7,0.7,1.5}, {0.1, 0.1, -1});
	PenduleSpherique PS(0.1, 0.2, 0.8, 0.00, 0.7, {0, 0}, {20,0.01}, {0, 5, 2}, {0,1,0});
	PlanFini PF({0,0,0}, {5,0,0}, {0,5,0}, 0.8, 0.00);
	PlanInfini PI({0,0,0}, {0,0,1}, 0.8, 0.00);
	PlanInfini PI2({0,0,0}, {0,0,1}, 0.8, 0.00);
	Boulet Bo(1.0, 0.1,0.8, 0.00, {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1});
	Systeme S;
	IntegrateurEulerCromer I;
	IntegrateurRungeKutta Runge;
	TextViewer Text(cout);
	//~ cout << BT << BT.evolution() << PI;
//======================================================================
//~ test collision balles
	//~ B1.ajoute(S);//B6.ajoute(S);c.ajoute_objet(S);
	//~ c.ajoute(S);
	//~ PI.ajoute(S);
	//~ shared_ptr<ObjetMobile> T = nullptr;
	//~ S.ajoute_objet(T);
	//~ for (int i(0); i <= 100; ++ i){
			//~ S.dessine_sur(Text);
			//~ S.evolue(I,1, 0.01);
	//~ }
	//S.getListeObjets()[0]->setPosition(Vecteur(3)); 
	//~ S.evolue(I, 2000, 0.01);
	
//======================================================================
//~ test rebonds balle-plan
	//~ PF.ajoute(S);
	//~ PI.ajoute(S); BT.ajoute(S);
	//~ PT.ajoute(S); 
	//~ c.ajoute(S);
	//~ cout << S;
	//~ S.evolue(I,1000,0.01);
//======================================================================
//~ deboggage
	//~ P1.ajoute(S);c.ajoute(S);
	//~ cout << S;
	//~ S.evolue(I, 2000, 0.01);
//======================================================================	
//~ test choc pendule-balle
	PI2.ajoute(S);
	B6.ajoute(S);
	P2.ajoute(S);
	c.ajoute(S);
	for (int i(0); i <= 200; ++ i){
			S.dessine_sur(Text);
			S.evolue(I,1, 0.01);
	}
//================Test limite plan fini=================================
	//~ B10.ajoute(S);
	//~ PF.ajoute(S);
	//~ P4.ajoute(S);
	//~ P5.ajoute(S);
	//~ B1.ajoute(S);
	//~ B2.ajoute(S);
	//~ c.ajoute(S);
	//~ Bo.ajoute(S);
	//~ for (int i(0); i <= 10; ++ i){
			//~ S.dessine_sur(Text);
			//~ S.evolue(I,1, 0.01);
	//~ }
//===================Test Ventilo=======================================
	//~ Vent v({0,0,0},{1,0,0},{0,1,0}, 8, 30);
	//~ cout << v;
	//~ Ventilateur V(Vent({0,0,0},{1,0,0},{0,1,0}, 4, 2), 0.5);
	//~ B9.ajoute(S);
	//~ c.ajoute(S);
	//~ Ventilateur V(v,0.5);
	//~ V.ajoute(S);
	//~ C1.ajoute(S);
	//~ cout << B9 << endl;
	//~ cout << B9;
	//~ v.ajoute(S);
	//~ cout << v << endl;
	//~ v.agit_sur(B9);
	//~ for (int i(0); i <= 750; ++ i){
			//~ S.dessine_sur(Text);
			//~ S.evolue(I,1, 0.01);
	//~ }
	//~ cout << v;
	//~ cout << S;
//======================================================================
//~ Bo.ajoute(S);
//~ PI.ajoute(S);
//~ c.ajoute(S);
	//~ for (int i(0); i <= 100; ++ i){
			//~ S.dessine_sur(Text);
			//~ S.evolue(I,1, 0.01);
	//~ }
//=======================Tst Brique=====================================
	}catch(Erreur E){E.affiche(); return 1;}
return 0;
}
