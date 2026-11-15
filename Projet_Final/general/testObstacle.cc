#include <iostream>
#include "Vecteur.h"
#include "Obstacle.h"
#include "ObjetMobile.h"
#include "ChampForces.h"
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;

int main(){
	PlanFini plan({0,0,0},{1,0,0},{0,1,0}, 0.8, 0.01);
//====================================================================
	Vecteur Longueur_b(0,-0.6,0);
	Vecteur Largeur_b(0.8,0,0);
	
	Brique brique({0,0,0.5}, Longueur_b, Largeur_b, 0.5, 0.8, 0.01);
//====================================================================
	double masse((M_PI*(0.2*0.2*0.2))*4);
	Balle balle(masse, 0.2, 0.8, 0.01, {1.2,-0.4,0.3},{0,0,-0.591725259488945}); 
//====================================================================
    cout<<"Nous avons :"<<endl;
    cout<<plan;
    cout<<endl;
    cout<<endl;
    cout<<brique;
    cout<<endl;
    cout<<endl;
    cout<<balle;
    cout<<endl;
//==========================Tests=====================================
//Positions de la balle:
Vecteur p1(1.2,-0.4,1.3);
Vecteur p2(0.2,-0.4,1.3);
//~~~~~~~~~~~~~~~~~~~~~~~
cout<<"tests :"<<endl;

cout<<endl;
cout<<plan.point_plus_proche(balle)<<" # point le plus proche plan"<<endl; //marche
cout<<plan.distance(balle)<<" # distance plan"<<endl;					   //marche 
cout<<brique.point_plus_proche(balle)<<" # point le plus proche brique"<<endl; //marche pas
cout<<brique.distance(balle)<<" # distance brique"<<endl; //marche pas
cout<<endl;
//------------------------------P1--------------------------------------
cout<<"Je depalce la balle en : ";
cout<<p1<<endl;
cout<<endl;
Balle balle1(masse, 0.2, 0.8, 0.01, p1,{0,0,-0.591725259488945}); 
//balle.setPosition(p1);
cout<<balle1;
cout<<endl;
cout<<"tests :"<<endl;
cout<<plan.point_plus_proche(balle1)<<" # point le plus proche plan"<<endl; //marche
cout<<plan.distance(balle1)<<" # distance plan"<<endl;					   //marche 
cout<<brique.point_plus_proche(balle1)<<" # point le plus proche brique"<<endl; //marche pas
cout<<brique.distance(balle1)<<" # distance brique"<<endl; //marche pas
cout<<endl;
cout<<endl;
//-------------------------------P2-------------------------------------
cout<<"Je depalce la balle en : ";
cout<<p2<<endl;
cout<<endl;
Balle balle2(masse, 0.2, 0.8, 0.01, p2,{0,0,-0.591725259488945}); 
//balle.setPosition(p2);
cout<<balle2;
cout<<endl;
cout<<"tests :"<<endl;
cout<<plan.point_plus_proche(balle2)<<" # point le plus proche plan"<<endl; //marche
cout<<plan.distance(balle2)<<" # distance plan"<<endl;					   //marche 
cout<<brique.point_plus_proche(balle2)<<" # point le plus proche brique"<<endl; //marche pas
cout<<brique.distance(balle2)<<" # distance brique"<<endl; //marche pas
cout<<endl;
cout<<endl;
return 0;
}
