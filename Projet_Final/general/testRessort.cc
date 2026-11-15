#include <iostream>
#include "ObjetMobile.h"
#include "Integrateur.h"
#include "ChampForces.h"
#include "constantes.h"
#include <cmath>
using namespace std;

void integre(ObjetMobile& R, IntegrateurEulerCromer& I, double p_temps = 0.1, unsigned int nb_integration  = 1000);

int main()
{
	ChampForces champ(g);
	Ressort R(0.1, 0.2, 0.8, 0.01, {0.4}, {0.0}, {0,0,1},
			 {0, sqrt(2)/2,-sqrt(2)/2}, 1.38165, 0.01, 0.0);
			 
	champ.agit_sur(R);
//	cout << R << endl;
	IntegrateurEulerCromer I;
	integre(R, I, 0.01, 10000);
	return 0;	
}
void integre(ObjetMobile& R, IntegrateurEulerCromer& I, double p_temps, unsigned int nb_integration){

	unsigned int compteur(1);
	while (compteur <= nb_integration){
		//cout << "L'integration " << compteur << " donne:" << endl;
		I.evolue(R, p_temps);
		//cout << R << endl;
		cout << R.getParam().getVecteur()[0] << " # x" << endl;
		++compteur;
	}
}
