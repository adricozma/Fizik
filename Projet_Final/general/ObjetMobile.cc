#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "ObjetMobile.h"
#include "Vecteur.h"
#include "ChampForces.h"
#include "constantes.h"
#include "Integrateur.h"
#include "Erreur.h"
#include "Systeme.h"
#include "Obstacle.h"
using namespace std;

ObjetMobile::ObjetMobile(double masse, double rayon, double alpha, double mu, 
		const Vecteur& p, const Vecteur& v,		//p(theta, phi)
		const Vecteur& O, const Vecteur& d)
		:param_(p), d_param_(v), force_(Vecteur(3)), origine_(O), mu_(mu),
		 rayon_(rayon), masse_(masse)
		{if (rayon_ <=  0.0) throw(Erreur("Constructeur ObjetMobile", "Rayon nul ou négatif"));
		 if (masse_ <= 0.0) throw(Erreur("Constructeur ObjetMobile", "Masse nulle ou négative"));
		 try{direction_ = ~d;}catch(Erreur E){E.setChemin("Constructeur ObjetMobile");throw E;}
		 if (abs(alpha) > 1.0) alpha_ = 1.0;
		 else alpha_ = abs(alpha);
		}
	//Gestion de quelques erreurs sur les constructeurs
	
const double ObjetMobile::getMasseVolumique() const{
	return (getMasse() / (4.0/3.0 * M_PI * getRayon() * getRayon() * getRayon()));
}

const double ObjetMobile::distance(const ObjetMobile& o) const{
	return (getPosition() - o.getPosition()).norme(); //Distamce cen
}

void ObjetMobile::agit_sur(ObjetMobile& o, const Integrateur& I, double dt){
try{
	const Vecteur n(~(getPosition() - o.getPosition())); //vecteur normal au point de choc
	const double alpha((getAlpha()+ o.getAlpha())/2.0);
	//~ if(getVitesse() * n > 0.0 and o.getVitesse() * n < 0.0) return;
	const double m1(getMasse()), m2(o.getMasse());
	const double lambda((1+alpha) * m2 / (m1 + m2)); 
	const double mu((getMu() + o.getMu())/2.0);
	const Vecteur F1(getResultanteForce());
	const Vecteur F2(o.getResultanteForce());
	Vecteur const& v1(getVitesse());
	Vecteur const& v2(o.getVitesse());
	
	const double Fn1(F1 * n);
	const double Fn2(F2 * n);
	
	if (Fn1 < 0){
		ajoute_force(-1 * Fn1  * n);
		o.ajoute_force(Fn1 * n); 
	}
	if (Fn2 > 0){
		ajoute_force(Fn2 * n);
		o.ajoute_force(-1 * Fn2 * n);
	}
	double v_star((v2 - v1) * n);
	const Vecteur v_c(v1 - v2 + v_star * n);
	Vecteur delta_v(0);
	try{
		if (7.0*mu*(1.0+alpha)*v_star >= 2.0*v_c.norme()) delta_v = (lambda*v_star*n - (2.0*m2 /(7.0*(m1+m2)))*v_c);
		else delta_v = (lambda * v_star * (n - mu*(~v_c)));
	}catch(Erreur E){delta_v = Vecteur(3);}
	//~ cout << "=============Affichage===========" << endl;
	//~ cout << "position 1 = " << getPosition() << endl;
	//~ cout << "position 2 = " << o.getPosition() << endl;
	//~ cout << "vitesse 1 = " << getVitesse() << endl;
	//~ cout << "vitesse 2 = " << o.getVitesse() << endl;
	//~ cout << "force 1 = " << getResultanteForce() << endl; 
	//~ cout << "force 2 = " << o.getResultanteForce() << endl; 
	
	//~ cout << "calculs : " << endl << endl;
	//~ cout << "n = " << n << endl;
	//~ cout << "lambda = " << lambda << endl;
	//~ cout << "F1n = " << Fn1 << endl;
	//~ cout << "F2n = " << Fn2 << endl;
	//~ cout << "v_star = " << v_star << endl;
	//~ cout << "v_c = " << v_c << endl;
	//~ cout << "7 mu (1+alpha) vstar = " << 7*mu*(1+alpha)*v_star << endl;	
	//~ cout << "2*v_c.norme() = " << 2*v_c.norme() << endl;
	//~ cout << endl << "v1 avant = " << v1 << endl;
	//~ cout << "v2 avant = " << v2 << endl;
	//~ cout <<  "dv = " << delta_v << endl;
	//~ cout << "v1 + delta_v = " << v1 + delta_v << endl;
	//~ cout << "v2 - (m1/m2) * delta_v = " << v2 - (m1/m2) * delta_v << endl;
	setVitesse(v1 + delta_v);
	o.setVitesse(v2 - (m1/m2) * delta_v);
	//~ cout << "v1 après = " << a1 << endl;
	//~ cout << "v2 après = " << a2 << endl;


//GESTION DES CAS AVEC CONTRAINTES GEOMETRIQUES
//L'idée ici est de retransmettre à l'objet 1 la partie de la vitesse 
//absorbée par les contraintes de l'objet 2, et vice versa.
		
	Vecteur const& a1(getVitesse());
	Vecteur const& a2(o.getVitesse());
	Vecteur temp1(v1 + delta_v), temp2(v2  - (m1/m2) * delta_v); //temp1 et temp 2 sont les vitesse que devraient avoir les objets après la collision
	Vecteur d1(a2 - temp2), d2(a1 - temp1);                      //d1 et d2 représentent la partie de la vitesse qu'il faudra àjouter aux objets 1 et 2
	if (d1 != Vecteur(d1.getVecteur().size())){
		setVitesse(a1 + (m2/m1) * d1);							 //Respecte la conservation de la quantité de mouvement
	}
	if (d2 != Vecteur(d2.getVecteur().size())){
		o.setVitesse(a2 + (m1/m2) * d2);
		
	}
//GESTION INTERPENETRATION 
//On a décidé de gérer l'interpénétration dans cette méthode.

	shared_ptr<ObjetMobile> o1(copie());
	shared_ptr<ObjetMobile> o2(o.copie());
	I.evolue(*o1,dt); I.evolue(*o2,dt);		//C'est un moyen de vérifier si l'objet est encore en choc. 
	if((*o1).choc(*o2)){					//On regarde si la copie, après un pas de temps dt, est encore imbriquée.
		const Vecteur& b1(getVitesse()), b2(o.getVitesse());
		const double L(getRayon() + o.getRayon());
		const Vecteur x1(getPosition()), x2(o.getPosition());
		const double e((b1 - b2) * (x1 - x2));
		const double nu((sqrt(L * L - ((x1-x2).norme2()) + e*e) - e)/(b1-b2).norme2());
		setPosition(x1 + nu * b1);
		o.setPosition(x2 + nu * b2);
	}
	o1.reset();
	o2.reset();
//Je décrémente manuellement le compteur du shared_ptr pour ètre sûr.
   }catch(Erreur E){E.setChemin("ObjetMobile::agit_sur()"); throw E;}
}

void ObjetMobile::reset_force(){
	force_ = Vecteur(force_.getSize());
}

bool ObjetMobile::choc(const ObjetMobile& o) const{
	if (distance(o) <=  getRayon() + o.getRayon()) return true;
//si la distance est trop grande, la méthode choc retourne false.
	return false;
}
bool ObjetMobile::choc(const Obstacle& o) const{
	if (o.distance(*this) <= getRayon()) return true;
	return false;
}

void ObjetMobile::ajoute(Systeme& S) const{
	shared_ptr<ObjetMobile> O = copie();
	S.ajoute_dessin(O);
	S.ajoute_objet(O);
//Par cette duplictaion de pointeur, l'objet restera lié à son dessin.
}
ostream& operator<<(ostream& sortie, ObjetMobile const& o){
	o.affiche(sortie);
	return sortie;
}
