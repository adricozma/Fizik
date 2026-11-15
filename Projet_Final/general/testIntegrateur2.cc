#include <iostream>
#define _USE_MATH_DEFINES
#include "ObjetMobile.h"
#include "Integrateur.h"
#include "constantes.h"
#include "ChampForces.h"
#include <cmath>
using namespace std;

void integre(ObjetMobile& R, Integrateur& I, double p_temps, unsigned int nb_integration){
	unsigned int compteur(1);
	while (compteur <= nb_integration){
		//~ cout << "L'integration " << compteur << " donne:" << endl;
		I.evolue(R, p_temps);
		//~ cout << R;
		cout << R.getPosition();
		cout << endl;
		++compteur;
	}
}

int main(){
	double M_V(3.0);
	double R(0.2);
	double M(M_V * 4.0/3.0 * M_PI * R * R * R);
	Balle B(M, R, 0.8, 0.01, {0,0,0}, {0, 0.1, 0.2});
	ChampForces c(g);
	c.agit_sur(B);
	IntegrateurEulerCromer I;
	//~ IntegrateurRungeKutta I;
	//cout << I << endl;
	//cout << B << endl;
	integre(B, I, 0.01, 1000);
	
	//~ Integrateur I1;
	//~ IntegrateurEulerCromer I2;
	//~ IntegrateurRungeKutta I3;
	//~ cout << I1 << endl << I2 << endl << I3;
	
	return 0;	
}
