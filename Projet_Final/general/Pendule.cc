#include <iostream>
#include "Vecteur.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "ObjetMobile.h"
#include "constantes.h"
#include "Dessinable.h"

using namespace std;

Pendule::Pendule(double masse, double rayon, double alpha, double mu, double longueur, double b, const Vecteur& p,const Vecteur& v,
				 const Vecteur& O, const Vecteur& d)
	:ObjetMobile(masse,rayon,alpha,mu,p,v,O), longueur_(longueur), b_(b) 
	{if (longueur_ <= 0.0) throw (Erreur("Constructeur Pendule","longueur négative ou nul"));
	 if (p.getSize() != 1 or v.getSize() != 1) throw (Erreur("Constructeur Pendule","Initilisation paramètres invalide"));
	 try{direction_ = ~d;}catch(Erreur E){E.setChemin("Constructeur Pendule");} //On re-initialise la direction pour utiliser la classe Erreur
	}

const Vecteur Pendule::evolution() const{
	Vecteur retour;
	const double& L(getLongueur());
	const double& b(getFrottement());
	const double& P1(getParam().getVecteur()[0]);
	const double& dP1(getDparam().getVecteur()[0]);
	const Vecteur& f(getForce());
	const Vecteur& d(getDirection());
	const double& m(getMasse());
	try{retour = Vecteur({(1 /(m * L)) * (cos(P1) * f * d - sin(P1) * f * (~g) - b/L * dP1)});}
	catch(Erreur E){E.setChemin("Pendule::evolution()");throw E;}
	return retour;
// Utilise le constructeur avec liste d'initialisation (une dimension ici).
//Pas indispensable de le faire ainsi mais cela permet de trouver plus facilement d'ou viennent certaines erreurs.	
}


const Vecteur Pendule::getPosition()const{
	Vecteur retour;
	const Vecteur& O(getOrigine());
	const Vecteur& d(getDirection());
	const double& L(getLongueur());
	const double& P1(getParam().getVecteur()[0]);
	try{retour = Vecteur(O + L*cos(P1)*(~g) + L*sin(P1)*d);}
	catch(Erreur E){E.setChemin("Pendule::getPosition()");throw E;}
	return retour;
// Utilise le constructeur de copie par défault ici pour retourner un vecteur
	
}
const Vecteur Pendule::u_theta() const{
	try	{return ~(getPosition() ^ getDirection() ^ getPosition());}
	catch(Erreur E){E.setChemin("Pendule::u_theta"); throw E;}
}
void Pendule::setPosition(const Vecteur& p){
	try{
		Vecteur projete(p.Projection(~g) + p.Projection(getDirection())); //On projète le vecteur p sur le plan d'oscillation du pendule.
		setParam(acos((~projete)*(~g))); //On utilise la définition du produit scalaire 
		}
	catch(Erreur E){E.setChemin("Pendule::setPosition()"); throw E;} 
}
void Pendule::setVitesse(const Vecteur& v){
//Reçoit en paramètre la nouvelle vitesse après un choc
try{
	Vecteur retour({1/getLongueur() * (v.Projection(u_theta())).norme()* -1});
	setDparam(retour);
	}
	catch(Erreur E){E.setChemin("Pendule::setVitesse()");throw E;}
// on utilise le fait que theta point vaut v/L avec v la norme de la vitesse et L la longueur du pendule
// le pendule est contraint de se déplacer dans un plan. Il faut donc trouver le vecteur unitaire U_theta pour projeter la vitesse résultante
// (due au choc) selon U_theta. Pour déterminer ensuite la nouvelle valeur du paramètre theta point, on sait que theta point = v/L
}

const Vecteur Pendule::getVitesse() const{
	Vecteur retour;
	const Vecteur& d(getDirection());
	const double& L(getLongueur());
	const double& P1(getParam().getVecteur()[0]);
	const double& dP1(getDparam().getVecteur()[0]);
	try{retour = Vecteur(L*dP1*(cos(P1)*d -sin(P1)*(~g)));}
	catch(Erreur E){E.setChemin("Pendule::getVitesse()"); throw E;}
	return retour;
// Constructeur de copie ici aussi
}

const Vecteur Pendule::getResultanteForce() const{
	Vecteur retour;
try{
	const Vecteur& d(getDirection());
	const double& P1(getParam().getVecteur()[0]);
	const double& dP1(getDparam().getVecteur()[0]);
	const double& L(getLongueur());
	const double& m(getMasse());
	retour = Vecteur(m*L*(evolution().getVecteur()[0] * (cos(P1)*d - sin(P1)*(~g))
				   - (dP1 * dP1 * (sin(P1) * d + cos(P1) *(~g)))));
	}catch(Erreur E){E.setChemin("Pendule::getResultanteForce()");throw E;}
	return retour;
}
		
void Pendule::affiche(ostream& sortie) const{
	sortie << "Un Pendule:" << endl;
	sortie << getMasse() << " # masse pendule" << endl;
	sortie << getRayon() << " # rayon pendule" << endl;
	sortie<<getAlpha()<<" # alpha pendule"<<endl;
	sortie<<getMu()<<" # mu pendule"<<endl;
	sortie << getLongueur() << " # longueur pendule" << endl;
	sortie << getFrottement() << " # frottement pendule" << endl;
	sortie << getOrigine() << " # origine pendule" << endl;
	sortie << getDirection()<< " # direction pendule" << endl;
	sortie << getParam().getVecteur()[0] << " # theta pendule" << endl;
	sortie << getDparam().getVecteur()[0] << " # dtheta pendule" << endl;
	sortie << evolution() << " # f() pendule" << endl;
	sortie << getPosition() << " # position bout pendule" << endl;
	sortie << getVitesse() << " # vitesse bout pendule" << endl;
	sortie << getResultanteForce() << " # resultante des forces" << endl;
}		
