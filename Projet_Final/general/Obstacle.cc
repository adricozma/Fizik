#include <iostream>
#include "Vecteur.h"
#include "Obstacle.h"
#include "ObjetMobile.h"
#include "constantes.h"
#include "Integrateur.h"
#include "Erreur.h"
#include "Systeme.h"
#include <vector>
#include <cmath>

using namespace std;

//------------Classe Obstacle----------------------------
Obstacle::Obstacle(const Vecteur& position,const Vecteur& normal, double alpha, double mu)
		:position_(position), alpha_(alpha), mu_(mu)
		{try{normal_ = (~normal); 
			}catch(Erreur E){E.setChemin("Constructeur Obstacle");}	
		}
		
double Obstacle::distance(const ObjetMobile& o) const{
	Vecteur d(o.getPosition() - point_plus_proche(o));
	return d.norme();
}
void Obstacle::agit_sur(ObjetMobile& o, const Integrateur& I, double dt) const{
try{	
	const Vecteur n(~(o.getPosition() - point_plus_proche(o)));
	const Vecteur v(o.getVitesse());
	const Vecteur w(o.getV_angulaire());
	const double R(o.getRayon());
	if (n * v > 0.0) return;	//Si l'objet s'éloigne, il n'y a pas de choc.
	const Vecteur F(o.getResultanteForce());
	const double Fn(F*n);
	const double mu((getMu() + o.getMu())/2.0);
	const double alpha((getAlpha()+ o.getAlpha())/2.0);
	
	
	const double v_star((-1.0) * v * n);
	const Vecteur v_c(v + (v_star * n) + (n ^ (R*w)));
	if (Fn < 0) {
		o.ajoute_force((-1.0) * Fn * n);
	}
	Vecteur delta_v;
	Vecteur delta_w;
		try{
			if (7.0*mu*(1.0+alpha)*v_star >= 2.0*v_c.norme()){
				delta_v = (1.0+alpha)*v_star*n - 2.0/7.0 *v_c;
				delta_w = (5.0/(7.0 * R)) * (n ^ v_c); 
			}else{
				delta_v = (1.0+alpha) *v_star * (n-mu * (~v_c));
				delta_w = (5.0/(2.0 * R) * mu * (1+alpha) * v_star)*(n^(~v_c));
			}
		}catch(Erreur E){delta_v = Vecteur(3); delta_w = Vecteur(3);} 
//Si v_c est nul, cela veut dire que l'objet est posé sur l'obstacle et/ou qu'il roule
		
	//~ cout << "calcul : " << endl;
	//~ cout << "n = " << n << endl;
	//~ cout << "Fn = " << Fn << endl;
	//~ cout << "v_star = " << v_star << endl;
	//~ cout << "v_c = " <<  v_c << endl;
	//~ cout << "7*mu*(1+alpha)*v_star = " << 7*mu*(1+alpha)*v_star << endl;
	//~ cout << "delta_v = " << delta_v << endl;
	//~ cout << "Je veux set : " << o.getVitesse() + delta_v << endl;
	//~ cout << "Vitesse = " << o.getVitesse() + delta_v << endl;
	o.setVitesse(v + delta_v); 
	//o.setV_angulaire(w + delta_w);
	//Dans cette partie, cette méthode fera aussi le calcul avec une copie de l'objet mobile
	//en l'intégrant pour voir s'il y  encore choc (avec la copie).
	//Si c'est le cas, alors l'Objet (pas la copie) sera déplacé.
	
	shared_ptr<ObjetMobile> temp = o.copie();
	I.evolue(*temp, dt);
	if ((*temp).choc(*this)){	//On regarde si la copie de l'objet est encore imbriquée après un pas de temps dt.
		double L(o.getRayon());
		const Vecteur& x1(o.getPosition()); // Position de l'Objet
		const Vecteur& x2(point_plus_proche(o)); // Point le plus proche de l'obstacle
		const Vecteur& v1(o.getVitesse());
		double e(v1 * (x1 - x2));
		double nu((sqrt(L * L - ((x1-x2).norme2()) + e*e) - e)/v1.norme2());
		o.setPosition(x1 + nu * v1);
	}
	temp.reset();
	//Je décrémente manuellement le compteur du shared_ptr pour ètre sûr
	}catch(Erreur E){E.setChemin("Obstacle::agit_sur()"); throw E;}
}
//-------------Classe PlanInfini-----------------------------
PlanInfini::PlanInfini(const Vecteur& Origine, const Vecteur& Normal, double alpha, double mu)
:Obstacle(Origine, Normal, alpha, mu)
{}

const Vecteur PlanInfini::point_plus_proche(const ObjetMobile& o) const{
	return o.getPosition()+((getPosition()-o.getPosition())*getNormal())*getNormal();
}

void PlanInfini::affiche(ostream& sortie) const{
	sortie<<"un mur plan: "<<endl;
	sortie<<getPosition()<<" # origine plan"<<endl;
	sortie<<getNormal()<<" # normale plan"<<endl;
	sortie<<getAlpha()<<" # alpha plan"<<endl;
	sortie<<getMu()<<" # mu plan"<<endl;
}
	
//-------------Classe PlanFini-------------------------------

PlanFini::PlanFini(const Vecteur& origine, const Vecteur& longueur, const Vecteur& largeur, double alpha, double mu, bool c) //const Vecteur& normal,
	: PlanInfini(origine,((longueur^largeur)), alpha, mu), longueur_(longueur), largeur_(largeur), couleur_(c)
 {}
//On ne peut pas gérer ici correctement l'eventuel erreur due au produit vectoriel, elle sera catch dans le main.
const Vecteur PlanFini::point_plus_proche(const ObjetMobile& o) const{
	Vecteur x_2(PlanInfini::point_plus_proche(o));
try{	
	Vecteur eL(~getLongueur());
	Vecteur el(~getLargeur());
	
	double x_kL((x_2-getPosition())*eL);
	double x_kl((x_2-getPosition())*el);
	
	if(x_kL>(getLongueur().norme())){
		x_2-=(x_kL-(getLongueur().norme()))*eL;
	}else if(x_kL<0){
		x_2-=((x_kL)*eL);
	}
	if(x_kl>(getLargeur().norme())){
		x_2-=(x_kl-(getLargeur().norme()))*el;

	}else if(x_kl<0){
		x_2-=((x_kl)*el);
	}
   }catch(Erreur E){E.setChemin("point_portion_plan");throw E;}
	return x_2;
}
void PlanFini::affiche(ostream& sortie) const{
	sortie<<"un plan fini: "<<endl;
	sortie<<getPosition()<<" # origine plan"<<endl;
	sortie<<getNormal()<<" # normale plan"<<endl;
	sortie<<getAlpha()<<" # alpha plan"<<endl;
	sortie<<getMu()<<" # mu plan"<<endl;
}	
//-------------Classe Brique--------------------------------------
Brique::Brique(const Vecteur& origine, const Vecteur& longueur, const Vecteur& largeur, double hauteur, double alpha, double mu, bool couleur) //const Vecteur& normal,
	:Obstacle(origine,(longueur^largeur), alpha, mu), longueur_(longueur),largeur_(largeur), hauteur_(hauteur), couleur_(couleur)
{//~ {try{
	//~ largeur_ =  largeur - (largeur*(~longueur))*(~longueur);
//~ }catch(Erreur E){E.setChemin("Constructeur Brique");}
}

const Vecteur Brique::point_plus_proche(const ObjetMobile& o) const{
	const Vecteur& eL(~getLongueur());    //simplifie l'ecriture
    const Vecteur& el(~getLargeur());
    const Vecteur& O(getPosition());
    const Vecteur& n(getNormal());
    
    const double L(getLongueur().norme());
    const double l(getLargeur().norme());
    const double h(getHauteur());
    
    PlanFini p1(O,L*eL,l*el,alpha_,mu_);
    PlanFini p2(O,(-1)*n*h,L*eL,alpha_,mu_);
    PlanFini p3(O,l*el,(-1)*h*n,alpha_,mu_);
    PlanFini p4(O+L*eL,(-1)*h*n,l*el,alpha_,mu_);
    PlanFini p5(O+l*el,L*eL,(-1)*h*n,alpha_,mu_);
    PlanFini p6(O-h*n,l*el,L*eL,alpha_,mu_);
	
	vector<PlanFini> tab={p1,p2,p3,p4,p5,p6};
	
	Vecteur x_2(p1.point_plus_proche(o));
	Vecteur x_temp;
	
	for(auto& p:tab){
		x_temp=p.point_plus_proche(o);
		if(((o.getPosition()-x_temp).norme())<((o.getPosition()-x_2).norme())){
			x_2=x_temp;
		}
	}
	
	return x_2;
}
void Brique::affiche(ostream& sortie) const{
	sortie<<"un mur brique: "<<endl;
	sortie<<getPosition()<<" # origine brique"<<endl;
	sortie<<getLongueur()<<" # longueur brique"<<endl;
	sortie<<getLargeur()<<" # largeur brique"<<endl;
	sortie<<getAlpha()<<" # alpha brique"<<endl;
	sortie<<getMu()<<" # mu brique"<<endl;
	sortie<<getHauteur()<<" # hauteur brique"<<endl;
}
//-----------Classe Sphere-------------------------------------------------------
Sphere::Sphere(const Vecteur& position, double rayon, double alpha, double mu)
:Obstacle(position, {0,0,1}, alpha, mu), rayon_(rayon)
{if (rayon <= 0.0) throw Erreur("Constructeur Sphere","rayon nul ou négatif");}

const Vecteur Sphere::point_plus_proche(const ObjetMobile& o) const{
	try{Vecteur v(o.getPosition()-getPosition());
		return getPosition()+getRayon()*(~(o.getPosition()-getPosition()));
	}catch(Erreur E){E.setChemin("Sphere::point_plus_proche()"); throw E;}
}

void Sphere::affiche(ostream& sortie) const{
	sortie << "Une sphère :" << endl;
	sortie << getPosition() << " # origine sphère" << endl;
	sortie << rayon_ << " # rayon sphère" << endl;
	sortie<<getAlpha()<<" # alpha sphère"<<endl;
	sortie<<getMu()<<" # mu sphère"<<endl;
}
//-------------------------------------------------------------------------------
Terrain::Terrain(string f_d, string f_p, double scale, double t_x, double t_y, double t_z,double v_max, double range,double scaleZ,
unsigned int div, vector<Vecteur> points_dessin)
	:Obstacle({0,0,0},{1,0,0}),f_dessin_(f_d), f_points_(f_p),
	scale_(scale), trans_x(t_x), trans_y(t_y), trans_z(t_z), v_max_(v_max), range_(range), scaleZ_(scaleZ),
	div_(div), points_dessin_({})
	//N_points_({})
{
	ifstream entree(f_dessin_);
	if((entree.fail())) throw Erreur("Constructeur Terrain","Ouverture fichier impossible");
		std::string element1;
		std::string element2;
		std::string element3;
		//double prev_x(1);
		//double prev_y(1);
		while(entree>>element1>>element2>>element3){
			if(!(entree.eof())){
				double x(stod(element1)); double y(stod(element2)); double z(stod(element3));
				Vecteur v({(x+trans_x)*scale_,
						   (y+trans_y)*scale_,
						   (z+trans_y)*scale_*getScaleZ()});
				points_dessin_.push_back(v);
			}
			
		}
		entree.close();
}
void Terrain::affiche(ostream& sortie) const{
	sortie<<getNom()<<endl;
}
//-------------------------------------------------------------------------------
const Vecteur Terrain::point_plus_proche(const ObjetMobile& o) const{
//méthode ou on considère simplement la distance aevc tous les autres points
	ifstream entree(f_points_);
	if((entree.fail())) throw Erreur("Terrain::point_plus_proche()", "Ouverture fichier impossible");
		string element1;
		string element2;
		string element3;
		
		entree>>element1>>element2>>element3;
		
		double d1(stod(element1)); double d2(stod(element2)); double d3(stod(element3));
		
		Vecteur prev_p({(d1+getTransX())*getScale(),(d2+getTransY())*getScale(),(d3+getTransZ())*getScale()*getScaleZ()});
		//~ Vecteur prev_p2;
		//~ Vecteur prev_p3;
		while(entree>>element1>>element2>>element3){
			if(!(entree.eof())){
				double x(stod(element1)); double y(stod(element2)); double z(stod(element3));
				Vecteur v({(x+getTransX())*getScale(),
						   (y+getTransY())*getScale(),
						   (z+getTransZ())*getScale()*getScaleZ()});
					if((o.getPosition()-v).norme()<=(o.getPosition()-prev_p).norme()){
						prev_p=v;
						//~ N_points_.push_back(v);
					}
					
			}
			
			
		}
		entree.close();
		return prev_p;
}
//-------------------------------------------------------------------------------
vector<Vecteur> Terrain::N_plus_proches(const ObjetMobile& o) const{
	vector<Vecteur> N_points;
	
	ifstream entree(f_points_);
	if((entree.fail())) throw Erreur("Terrain::N_plus_proche()", "Ouverture fichier impossible");
		std::string element1;
		std::string element2;
		std::string element3;
		
		entree>>element1>>element2>>element3;
		
		double d1(stod(element1)); double d2(stod(element2)); double d3(stod(element3));
		
		Vecteur prev_p({(d1+getTransX())*getScale(),(d2+getTransY())*getScale(),(d3+getTransZ())*getScale()*getScaleZ()});
		while(entree>>element1>>element2>>element3){
			if(!(entree.eof())){
				double x(stod(element1)); double y(stod(element2)); double z(stod(element3));
				Vecteur v({(x+getTransX())*getScale(),
						   (y+getTransY())*getScale(),
						   (z+getTransZ())*getScale()});
					if((o.getPosition()-v).norme()<(o.getPosition()-prev_p).norme()){
						prev_p=v;
						//~ if(v!=N_points.back()){
						    
							N_points.push_back(v);
						//~ }
					}
					
			}
				
		}
		entree.close();
		return N_points;
}
//-------------------------------------------------------------------------------
void Terrain::agit_sur(ObjetMobile& o, const Integrateur& I, double dt) const{
	vector<Vecteur> N_points(N_plus_proches(o));
	size_t taille(N_points.size());
	cout<<endl;
	cout<<"----------"<<taille<<"------"<<endl;
	cout<<endl;
	//~ N_plus_proches(o).clear();
	//~ N_plus_proches(o).shrink_to_fit();
	
	Vecteur origine;
	try{
	Vecteur normal;
	Vecteur prev_n({0,0,1}); //Si notre liste ne contient pas assez d'elements
	if(taille>=3){
		//cout<<N_points[taille-2]<<"---"<<N_points[taille-3]<<"---"<<N_points[taille-]<<endl;
		origine=N_points[taille-1];
		Vecteur n((origine-N_points[taille-2])^(origine-N_points[taille-3]));
		normal=n;
		prev_n=n;
	}else{
		origine=o.getPosition()-(~o.getVitesse())* o.getRayon();
		normal=prev_n;
	}
	if(normal.norme()<=epsilon){normal={0,0,1};}//Simplement pour éviter un vecteur nul dans le constructeur

	PlanInfini p(origine, normal);
	p.agit_sur(o,I,dt);
	}catch(Erreur e){e.setChemin("Terrain::agit_sur()");throw e;}
}
//-------------------------------------------------------------------------------
void Obstacle::ajoute(Systeme& S) const{
	shared_ptr<Obstacle> O(copie());
	S.ajoute_dessin(O);
	S.ajoute_obstacle(O);
//Duplication de pointeur pour préserver la liaison objet/dessin
}
ostream& operator<<(ostream& sortie, Obstacle const& o){
	o.affiche(sortie);
	return sortie;
}

