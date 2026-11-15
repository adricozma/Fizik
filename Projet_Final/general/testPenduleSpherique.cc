#include <iostream>
#include "ObjetMobile.h"
#include "ChampForces.h"
#include "Integrateur.h"
#include "constantes.h"

using namespace std;

void integre(ObjetMobile& R, const IntegrateurEulerCromer& I, double p_temps, unsigned int nb_integration);

int main(){
	
	ChampForces c(g);	
	PenduleSpherique P(0.1, 0.2,0.8, 0.01, 0.7, {3, 4}, {1.0,1.0}, {0, 5, 2}, {0,1,0});
	IntegrateurEulerCromer I;
	
	c.agit_sur(P);
	integre(P,I, 0.01, 5000);

return 0;	
}

void integre(ObjetMobile& O, const IntegrateurEulerCromer& I, double p_temps, unsigned int nb_integration){

	unsigned int compteur(1);
	while (compteur <= nb_integration){
		//cout << "L'integration " << compteur << " donne:" << endl;
		I.evolue(O, p_temps);
		//cout << R << endl;
		cout << O.getPosition() << endl;
		++compteur;
	}
}
