#pragma once
#include <iostream>
#include <cmath>
#include "Vecteur.h"
#include "ObjetMobile.h"

class Balle: public ObjetMobile {
	private:
		
	public: 
//=======================Constructeur==============================//
		 Balle(double masse_vol=0., double rayon=1.0, 
		 const Vecteur& p={0,0,0}, const Vecteur& v={0,0,0}, const Vecteur& f={0,0,0});
		 	
//==========================Méthodes===============================//		
		//~ void ajoute_force(Vecteur const& df){force_+=df;}
		Vecteur evolution();
//======================Getters====================================//
		const Vecteur& getPosition() const{return getParam();}
		const Vecteur& getVitesse() const{return getDparam();}
//======================Setters====================================//
		
	
};

	std::ostream& operator<<(std::ostream& sortie, Balle const& b);
