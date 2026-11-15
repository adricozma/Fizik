#include "ObjetMobile.h"
#include "constantes.h"

using namespace std;


Ressort::Ressort(double masse, double rayon, double alpha, double mu,
		const Vecteur& p, const Vecteur& v, const Vecteur& O, 
		const Vecteur& d, double k, double b, double longueur_a_vide)
		:ObjetMobile(masse, rayon, alpha, mu, p, v, O), k_(k), b_(b), longueur_a_vide_(longueur_a_vide)
		{if (p.getSize() != 1 or v.getSize() != 1) throw Erreur("Constructeur Ressort","Initialisation parametre invalide");
		 try{direction_ = ~d;}catch(Erreur E){E.setChemin("Constructeur Ressort");} //On re-initialise la direction pour utiliser la classe Erreur.
		}
		//on garde un rayon même si on ne l'utilise pas, c'est au cas on y attacherait une balle au bout.
		//ou alors ce sera utile pour les chocs.

const Vecteur Ressort::evolution() const{
	if (abs(getMasse()) < epsilon) throw ("masse nul");
	return Vecteur({(1.0/getMasse())*(getForce()*getDirection()
	 - getRaideur() * getParam().getVecteur()[0] - getFrottement() * getDparam().getVecteur()[0])});
}	

const Vecteur Ressort::getPosition() const{
	return Vecteur(getOrigine() + getParam().getVecteur()[0] * getDirection());
}

const Vecteur Ressort::getVitesse() const{
	return Vecteur(getDparam().getVecteur()[0] * getDirection());
}

const Vecteur Ressort::getAttache() const{
	return getOrigine() + (getLongueur() * getDirection()).oppose();
}
void Ressort::setVitesse(const Vecteur& v){
	try{
		setDparam(Vecteur(v.Projection(getDirection())));
	}catch(Erreur E){E.setChemin("Ressort::setVitesse()");}
}

const Vecteur Ressort::getResultanteForce() const{
	return Vecteur(getMasse() * (evolution().getVecteur()[0] * getDirection()));
	//F = m*a ou F et a sont des vecteur. 
	//Pour obtenir a, on multiplie le vecteur dirction par le scalaire obtenu au travers de evolution().
}

void Ressort::affiche(ostream& sortie) const{
	sortie << "Un ressort :" << endl;
	sortie << getMasse() << " # masse ressort" << endl;
	sortie << getRayon() << " # rayon ressort" << endl;
	sortie<<getAlpha()<<" # alpha ressort"<<endl;
	sortie<<getMu()<<" # mu ressort"<<endl;
	sortie << getRaideur() << " # raideur ressort" << endl;
	sortie << getFrottement() << " # frottement ressort" << endl;
	sortie << getOrigine() << " # origine ressort" << endl;
	sortie << getDirection() << " # direction ressort" << endl;
	sortie << getParam() << " # x ressort" << endl;
	sortie << getDparam() << " # dx ressort" << endl;
	sortie << evolution() << " # f() ressort" << endl;
	sortie << getPosition() << " # position bout ressort" << endl;
	sortie << getVitesse() << " # vitesse bout ressort" << endl;
}
