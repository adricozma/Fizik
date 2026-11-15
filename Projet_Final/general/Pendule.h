#pragma once
#include "Vecteur.h"
#include <cmath>
//#include "Balle.h"
#include "ObjetMobile.h"

class Pendule: public ObjetMobile{
	private:
		double longueur_;
		double coeff_frot_;
	public: 
		Pendule(double massse, double longueur, const Vecteur& p={0}, 
		const Vecteur& v={0,0,0}, const Vecteur& f={0,0,0});
		
		Vecteur evolution();
	
};
