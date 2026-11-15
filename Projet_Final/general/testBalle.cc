#include <iostream>
#include "Vecteur.h"
#include "ObjetMobile.h"
#include "ChampForces.h"
#include "constantes.h"
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;

int main(){
	//Vecteur v1(3), v2(3), v3(g);
	double M_V(3.0), R(0.2), M(M_V * (M_PI * 4.0 / 3.0 * R * R * R));
	ChampForces c(g);
	Balle b1(M,R);
	//~ Balle b2(-0.1,1);
	Balle b3;
	Balle B6(1.0,0.1,0.8, 0.01, {0.5,0.5,0.1}, {-1.0,-1.0,0});
	c.agit_sur(b1);
	b1.ajoute_force(~g);
	cout << B6;
	
	cout<<b1<<": Balle 1"<<endl;
	Vecteur force1(0,1,1);
	b1.ajoute_force(force1);
	cout<<b1<<": Balle 1 + Force"<<endl;
	
	//~ cout<<b2<<": Balle 2"<<endl;
	//~ Vecteur force2(0,0,2000);
	//~ b2.ajoute_force(force2);
	//~ cout<<b2<<": Balle 2 + Force"<<endl;
	
	cout<<b3<<": Balle 3"<<endl;
	Vecteur force3(-10,-10,-10);
	b3.ajoute_force(force3);
	cout<<b3<<": Balle 3 + Force"<<endl;
	
	
	Balle b5(0,0,0);
	cout<<b5<<": Balle 5"<<endl;
	
	//~ ChampForces c(g);
	c.agit_sur(b5);
	cout<<b5<<": Balle 5 + Champ"<<endl;
	
	
	return 0;
}
