#include "ObjetMobile.h"

using namespace std;

Boulet::Boulet(double m, double r, double alpha, double mu, 
			   Vecteur p, const Vecteur& p_ang, Vecteur v, const Vecteur& v_ang)
:ObjetMobile(m,r,alpha,mu,p.augmente(p_ang),v.augmente(v_ang))
{
	if (param_.getSize() != 6 or d_param_.getSize() != 6) throw Erreur("Constructeur Boulet","Vecteur de taille invalide ");
}

void Boulet::setPosition(const Vecteur& P){
	if (P.getSize() != 3) throw Erreur("Boulet::setPosition()","Vecteur de taille invalide");
//Les boulets n'évolueront que dans un espace en 3 dimensions.
	const Vect& pv(getParam().getVecteur());
	Vecteur retour(P);
	Vecteur temp({pv[3],pv[4],pv[5]});
	retour.augmente(temp);
	setParam(retour);
}
void Boulet::setVitesse(const Vecteur& V){
	if (V.getSize() != 3) throw Erreur("Boulet::setVitesse()","Vecteur de taille invalide");	
	const Vect& pv(getDparam().getVecteur());
	Vecteur retour(V);
	Vecteur temp({pv[3],pv[4],pv[5]});
	retour.augmente(temp);
	setDparam(retour);
}
void Boulet::setP_angulaire(const Vecteur& P){
	if (P.getSize() != 3) throw Erreur("Boulet::setP_angulaire()","Vecteur de taille invalide");	
	const Vect& pv(getParam().getVecteur());
	Vecteur temp({pv[0],pv[1],pv[2]});
	temp.augmente(P);
	setParam(P);
}
void Boulet::setV_angulaire(const Vecteur& V){
	if (V.getSize() != 3) throw Erreur("Boulet::setV_angulaire()","Vecteur de taille invalide");	
	const Vect& pv(getDparam().getVecteur());
	Vecteur temp({pv[0],pv[1],pv[2]});
	temp.augmente(V);
	setDparam(V);
}
const Vecteur Boulet::getPosition() const{
	const Vect& pv(getParam().getVecteur());
		return Vecteur({pv[0],pv[1],pv[2]});
}
const Vecteur Boulet::getP_angulaire() const{
	const Vect& pv(getParam().getVecteur());
	return Vecteur({pv[3],pv[4],pv[5]});	
}
const Vecteur Boulet::getVitesse() const{
	const Vect& pv(getDparam().getVecteur());
	return Vecteur({pv[0],pv[1],pv[2]});		
}
const Vecteur Boulet::getV_angulaire() const{	
	const Vect& pv(getDparam().getVecteur());
	return Vecteur({pv[3],pv[4],pv[6]});	
}
const Vecteur Boulet::evolution() const{
	Vecteur v(getForce()*(1/getMasse()));
	v.augmente(Vecteur(3));
	return v;	
}
void Boulet::affiche(std::ostream& sortie) const{
	sortie<<"un boulet: "<<endl;
	sortie<<getMasse()<<" # masse"<<endl;
	sortie<<getRayon()<<" # rayon"<<endl;
	sortie<<getAlpha()<<" # alpha"<<endl;
	sortie<<getMu()<<" # mu"<<endl;
	sortie<<getMasseVolumique()<<" # masse volumique"<<endl;
	sortie<<getPosition()<<" # position"<<endl;
	sortie<<getVitesse()<<" # vitesse"<<endl;
	sortie<<getP_angulaire()<<" # position angulaire"<<endl;
	sortie<<getV_angulaire()<<" # vitesse angulaire"<<endl;
	sortie<<getForce()<<" # force"<<endl;
}
