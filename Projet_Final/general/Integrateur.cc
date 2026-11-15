#include "Integrateur.h"
#include "ObjetMobile.h"
#include <iostream>
using namespace std;

void Integrateur::evolue(ObjetMobile& O, double dt) const{
	const Vecteur d2P(O.evolution());	//Garde en mémoire les ancien paramètres pour évolution.
	O.setParam(O.getParam() + dt * O.getDparam()); 
	O.setDparam(O.getDparam() + dt * d2P); 
}
void IntegrateurEulerCromer::evolue(ObjetMobile& O, double dt) const{
	O.setDparam(O.getDparam() + dt * O.evolution());
	O.setParam(O.getParam() + dt * O.getDparam());
}


void IntegrateurRungeKutta::evolue(ObjetMobile& O, double dt) const{
	const Vecteur k1(O.getDparam());
	const Vecteur dk1(O.evolution());
	const Vecteur k2(O.getDparam() * ((dt/2) * dk1));
	shared_ptr<ObjetMobile> temp2(O.copie());
	shared_ptr<ObjetMobile> temp3(O.copie());
	shared_ptr<ObjetMobile> temp4(O.copie()); 	//Crée des copies de O pour pouvoir modifier les attributs pour les calculs
		
		
		(*temp2).setParam((*temp2).getParam() + (dt / 2.0) * k1);
		(*temp2).setDparam((*temp2).getDparam() + (dt / 2.0) * dk1);
	const Vecteur dk2((*temp2).evolution());
	const Vecteur k3(O.getDparam() + (dt / 2.0) * dk2);
		(*temp3).setParam((*temp3).getParam() + (dt / 2.0) * k2);
		(*temp3).setDparam((*temp3).getDparam() + (dt / 2.0) * dk2);
	const Vecteur dk3((*temp3).evolution());
	const Vecteur k4(O.getDparam() + (dt / 2.0) * dk3);
		(*temp4).setParam((*temp4).getParam() + dt * k3);
		(*temp4).setDparam((*temp4).getDparam() + dt * dk3);
	const Vecteur dk4((*temp4).evolution());
	
	O.setParam(O.getParam() + ((dt / 6.0) * (k1 + 2*k1 + 2*k3 + k4)));
	O.setDparam(O.getDparam() + ((dt /6.0) * (dk1 + 2*dk2 + 2*dk3 + dk4)));
	temp2.reset();
	temp3.reset();
	temp4.reset();
}

