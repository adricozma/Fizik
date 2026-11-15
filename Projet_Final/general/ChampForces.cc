#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "ChampForces.h"
#include "Vecteur.h"
#include "ObjetMobile.h"
#include "Systeme.h"
#include "Erreur.h"
using namespace std;


//ChampForces::ChampForces(Vecteur intensite=g);

ChampForces::ChampForces(const Vecteur& intensite)
		:intensite_(intensite)
		{}
//=================================================================================//		
void ChampForces::agit_sur(ObjetMobile& o) const{
	o.ajoute_force(o.getMasse() * intensite_);
}
void ChampForces::ajoute(Systeme& S) const{
	shared_ptr<ChampForces> O = copie();
	S.ajoute_champ(O);
}
Vent::Vent(const Vecteur& origine, const Vecteur& longueur, const Vecteur& largeur, double profondeur, double V0)
:ChampForces(3.77 * V0 * V0 * (~(longueur ^ largeur))), origine_(origine), normal_(~(longueur ^ largeur)), longueur_(longueur),
profondeur_(profondeur), V0_(V0)
{try{
	largeur_ =  largeur - (largeur*(~longueur))*(~longueur);
}catch(Erreur E){E.setChemin("Constructeur Vent");}}//intensite_ vaut 3.77 * V0^2 * n
bool Vent::dedans(const ObjetMobile& O)const{
try{
	double L(longueur_.norme()), l(largeur_.norme());
	const Vecteur& n(normal_);
	const Vecteur eL(~longueur_);
	const Vecteur el(~largeur_);
	const Vecteur p(origine_ - O.getPosition());
	bool T1(p * n < 0), T2(abs(p * n) < profondeur_), T3(p * el < 0);
	bool T4(abs(p * el) < l), T5(p * eL < 0), T6(abs(p * eL) < L);
	//J'ai construit le ventilateur à l'envers par rapport à l'exemple.
	//Donc les tests sont différents.
	return (T1 and T2 and T3 and T4 and T5 and T6);
}catch(Erreur E){E.setChemin("Vent::dedans()"); throw E;}
}
void Vent::agit_sur(ObjetMobile& O) const{
	if (dedans(O)){ 
		O.ajoute_force(getIntensite() * O.getRayon() * O.getRayon());};
}
//============================Opérateur=============================================//
void ChampForces::affiche(ostream& sortie) const{
	sortie << "Un champ :" << endl; 
	sortie<< getIntensite();
	sortie<<" #intensité"<<std::endl;	
}
void Vent::affiche(ostream& sortie) const{
	sortie << "Un vent : " << endl;
	sortie << getIntensite() << " #intensité"<<endl;
	sortie << getOrigine() << " # Origine" << endl;	
	sortie << getLongueur() << " # Longueur" << endl;
	sortie << getLargeur() << " # Largeur" << endl;
	sortie << getNormal()  << " # Normal" << endl;
	sortie << getProfondeur() << " # Profondeur"  << endl;
}
ostream& operator<<(ostream& sortie, ChampForces const& c){
	c.affiche(sortie);
	return sortie;
}
