#include <iostream>
#include "Vecteur.h"
#include "ObjetMobile.h"
#include "constantes.h"
#include "Integrateur.h"
#include "ChampForces.h"
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;

void integre(ObjetMobile& R, Integrateur& I, double p_temps, unsigned int nb_integration);

int main(){
	ChampForces c(g);
	double R(1.0), M_V(0.3), M(M_V * 4.0/3.0 * M_PI * R * R * R);
	Pendule P(0.1, 1.0, 0.8, 0.01,0.2, 0.005, {0.4}, {0.0}, {0,2,1}, {0,1,0});
	Pendule P2(1.25664, 1.0, 2, 0.005, {4}, {40}, {0,2,2}, {0,1,0});
	Pendule P3(M,R, 0.8, 0.01, 2.0, 0.005, {0.4}, {0.4},{0,2,2} ,{0,1,0});
	//cout << P << endl;
	IntegrateurEulerCromer I;
	//~ cout << P3 << endl;
	c.agit_sur(P3);
	integre(P3, I, 0.01, 2000);
	//~ cout << P2;
	return 0;
}

void integre(ObjetMobile& O, Integrateur& I, double p_temps, unsigned int nb_integration){

	unsigned int compteur(1);	
	
	while (compteur <= nb_integration){
		//cout << "L'integration " << compteur << " donne:" << endl;
		I.evolue(O, p_temps);
		//cout << O << endl;
		//cout << O.getParam().getVecteur()[0] << "# theta pendule" << endl;
		cout << O.getParam() << endl;
		//~ cout << O.getPosition() << endl;
		++compteur;
	}
}
