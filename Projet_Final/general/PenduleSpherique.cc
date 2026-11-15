#include <iostream>
#include "ObjetMobile.h"
#include "constantes.h"
#include "Dessinable.h"
#include <cmath>

using namespace std;

PenduleSpherique::PenduleSpherique(double masse, double rayon,double alpha, double mu,
		double longueur, const Vecteur& p, const Vecteur& v, const Vecteur& O, const Vecteur& d)
		:ObjetMobile(masse, rayon, alpha, mu, p, v, O, d), longueur_(longueur) 
		{if (longueur_ <= 0.0) throw Erreur("Constructeur PenduleSpherique","longueur nulle");
		 if (masse_ <= 0.0)    throw Erreur("Constructeur PenduleSpherique","masse nulle");
		 if (p.getSize() != 2 or v.getSize() != 2) throw (Erreur("Constructeur PenduleSpherique","Initilisation paramètres invalide"));
		 try{direction_ = ~d;}catch(Erreur E){E.setChemin("Constructeur PenduleSpherique");} //On re-initialise la direction pour utiliser la classe Erreur
		}
			
void PenduleSpherique::setVitesse(const Vecteur& v){
try{
	const double& P1(getParam().getVecteur()[0]);   // Theta
	const double& P2(getParam().getVecteur()[1]);   // Phi
	const Vecteur& d(getDirection());
	
	const Vecteur u_theta((cos(P1) * cos(P2)) * d
						 +((cos(P1) * sin(P2)) * d ^ (~g))
						 - (sin(P1) * (~g)));
	
	const Vecteur u_phi(-sin(P2) * d + (cos(P2) * d ^(~g)));
	
	setDparam(Vecteur({v * u_theta, v * u_phi}));
   }catch(Erreur E){E.setChemin("PenduleSpherique::setVitesse()"); throw E;}
}
			
const Vecteur PenduleSpherique::evolution() const{
	const double& P1(getParam().getVecteur()[0]);   // Theta
	const double& dP1(getDparam().getVecteur()[0]); // dTheta
	const double& dP2(getDparam().getVecteur()[1]); // dPhi
	const double& L(getLongueur());
//Rend le code plus lisible et facilite le déboggage
	double retour(sin(P1) * (cos(P1) * dP2 * dP2 - g.norme() * (1.0/L)));
	
	if (abs(P1) < 1e-2)  return Vecteur({retour,0});	
//Evite les "explosions" lorsque theta tend vers 0;
	else return Vecteur({retour, (-2.0 * (1.0 / tan(P1)) * dP1 * dP2)});
}

const Vecteur PenduleSpherique::getPosition() const{
try{
	const double& P1(getParam().getVecteur()[0]);   // Theta
	//const double& dP1(getDparam().getVecteur()[0]); // dTheta
	const double& P2(getParam().getVecteur()[1]);   // Phi
	//const double& dP2(getDparam().getVecteur()[1]); // dPhi
	const double& L(getLongueur());
	const Vecteur& O(getOrigine());
	const Vecteur& d(getDirection());
	
	return Vecteur(O + L * cos(P1) * (~g) + L * sin(P1) * cos(P2) * d
				   + ((L * sin(P1) * sin(P2) * d) ^ (~g)));
//Constructeur de copie (pas obligatoire, mais plus explicite)
   }catch(Erreur E){E.setChemin("PenduleSpherique::getPosition()"); throw E;}
}

const Vecteur PenduleSpherique::getVitesse() const{
try{
	const double& P1(getParam().getVecteur()[0]);   // Theta
	const double& dP1(getDparam().getVecteur()[0]); // dTheta
	const double& P2(getParam().getVecteur()[1]);   // Phi
	const double& dP2(getDparam().getVecteur()[1]); // dPhi
	const double& L(getLongueur());
	const Vecteur& d(getDirection());
	
	return Vecteur(L * (-1.0 * dP1*sin(P1)*(~g) + (dP1*cos(P1)*cos(P2) -dP2*sin(P1)*sin(P2))*d
				   + (dP1*cos(P1)*sin(P2) + dP2*sin(P1)*cos(P2))*(d^(~g))));
   }catch(Erreur E){E.setChemin("PenduleSpherique::getVitesse()"); throw E;}
}

const Vecteur PenduleSpherique::getResultanteForce() const {
try{
	const double& P1(getParam().getVecteur()[0]);   // Theta
	const double& dP1(getDparam().getVecteur()[0]); // dTheta
	const double& P2(getParam().getVecteur()[1]);   // Phi
	const double& dP2(getDparam().getVecteur()[1]); // dPhi
	const double& L(getLongueur());
	const double& m(getMasse());
	const Vecteur& d(getDirection());

	const Vecteur& f(evolution());
	const double& f1(f.getVecteur()[0]);
	const double& f2(f.getVecteur()[1]);

//===========Vecteur unitaire coordonnéees sphériques===================

	const Vecteur u_rho((sin(P1) * cos(P2)) * d 
					  +((sin(P1) * sin(P2)) * d ^(~g)) 
					  +  cos(P1) * (~g));
	
	const Vecteur u_theta((cos(P1) * cos(P2)) * d
						 +((cos(P1) * sin(P2)) * d ^ (~g))
						 - (sin(P1) * (~g)));
	
	const Vecteur u_phi(-sin(P2) * d + (cos(P2) * d ^(~g)));

//====================Forces résultantes================================
	
	return Vecteur(m*L*((- dP1 * dP1 - dP2 * dP2 * sin(P1) * sin(P1)) * u_rho
					   + (f1 - dP2 * dP2 * sin(P1) * cos(P1)) * u_theta
					   + (f2 * sin(P1) - 2.0 * dP1 * dP2 * cos(P1)) * u_phi));
   }catch(Erreur E){E.setChemin("PenduleSpherique::getResultanteForce()");throw E;}
}


 void PenduleSpherique::affiche(ostream& sortie) const {
	sortie << getMasse() << " # masse pendule" << endl;
	sortie << getRayon() << " # rayon pendule"<<endl;
	sortie<<getAlpha()<<" # alpha pendule"<<endl;
	sortie<<getMu()<<" # mu pendule"<<endl;
	sortie << getLongueur() << " # longueur pendule" << endl;
	sortie << getOrigine() << " # origine pendule" << endl;
	sortie << getDirection()<< " # direction pendule" << endl;
	sortie << getParam().getVecteur()[0] << " # theta pendule" << endl;
	sortie << getDparam().getVecteur()[0] << " # dtheta pendule" << endl;
	sortie << getParam().getVecteur()[1] << " # phi pendule" << endl;
	sortie << getDparam().getVecteur()[1] << " # dphi pendule" << endl;
	sortie << evolution() << " # f() pendule" << endl;
	sortie << getPosition() << " # position bout pendule" << endl;
	sortie << getVitesse() << " # vitesse bout pendule" << endl;
	
}
