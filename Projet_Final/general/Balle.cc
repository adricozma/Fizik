#include <iostream>
#include "Vecteur.h"
#include "ObjetMobile.h"
#include "Dessinable.h"
#include "constantes.h"
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

void Balle::affiche(ostream& sortie) const{
	sortie<<"une balle: "<<endl;
	sortie<<getMasse()<<" # masse"<<endl;
	sortie<<getRayon()<<" # rayon"<<endl;
	sortie<<getAlpha()<<" # alpha"<<endl;
	sortie<<getMu()<<" # mu"<<endl;
	sortie<<getMasseVolumique()<<" # masse volumique"<<endl;
	sortie<<getPosition()<<" # position"<<endl;
	sortie<<getVitesse()<<" # vitesse"<<endl;
	sortie<<getForce()<<" # force"<<endl;
}

Balle::Balle(double masse, double rayon, double alpha, double mu, const Vecteur& p, const Vecteur& v)
	:ObjetMobile(masse, rayon, alpha, mu, p, v)
//On place l'origine à la position initiale p
	{}

const Vecteur Balle::evolution() const{
	return Vecteur(getForce()*(1/getMasse()));
}

void Balle::ajoute_force(const Vecteur& df){
	if (df  == g * getMasse()){ // On utilise la surcharge de l'opérateur == qui fait la comparaison avec epsilon.
//Si on ajoute la force du au champ de gravité, on prend alors en compte la poussée d'Archimède.
	const double r_air=1.2; 
	const double scalaire(getMasse()-4.0*M_PI*r_air*(getRayon()*getRayon()*getRayon())/3.0);
	const Vecteur Force(g*scalaire);
		ObjetMobile::ajoute_force(Force);
	}
	else ObjetMobile::ajoute_force(df);
}


