#pragma once
#include <iostream>
#include <fstream>
#include "Vecteur.h"
#include "Dessinable.h"
#include "support_a_dessin.h"
#include <memory>
class ObjetMobile;
//Prédéclaration de la classe ObjetMobile à cause de la dépendence cyclique 
class Integrateur;

class Obstacle : public Dessinable{
	public:
//--------------------Constructeur--------------------------------------
//----------------------------------------------------------------------
		Obstacle(const Vecteur& position, const Vecteur& normal, double alpha = 0.8, double mu = 0.01);
		virtual ~Obstacle() = default;
//----------------------Méthodes----------------------------------------
//----------------------------------------------------------------------
		virtual void agit_sur(ObjetMobile& o, const Integrateur& I, double dt = 0.01) const;
		double distance(const ObjetMobile& o) const;
		virtual const Vecteur point_plus_proche(const ObjetMobile& o) const =0;
		void ajoute(Systeme& S) const;
		virtual void affiche(std::ostream& sortie) const = 0;
		virtual std::shared_ptr<Obstacle> copie() const = 0;
//---------------------getters------------------------------------------
//----------------------------------------------------------------------
		const Vecteur& getPosition() const{return position_;}
		const Vecteur& getNormal() const{return normal_;}
		const double getAlpha() 						const{return alpha_;}
		const double getMu()							const{return mu_;}
	protected:
//---------------------Attributs----------------------------------------
//----------------------------------------------------------------------
		Vecteur position_;
		Vecteur normal_;
		double alpha_;
		double mu_;
};

std::ostream& operator<<(std::ostream& sortie, Obstacle const& o);

class PlanInfini: public Obstacle{
	private:
		std::shared_ptr<PlanInfini> CloneMe() const {return std::shared_ptr<PlanInfini>(new PlanInfini(*this));}
	public:
		PlanInfini(const Vecteur& Origine={0,0,0}, const Vecteur& Normal={0,0,1}, double alpha = 0.8, double mu = 0.01);
		
		virtual const Vecteur point_plus_proche(const ObjetMobile& o) const override;
		virtual void affiche(std::ostream& sortie) const override;
		std::shared_ptr<Obstacle> copie() const override{return CloneMe();}
		virtual void dessine_sur(SupportADessin& support) const override {support.dessine(*this); }
		
};

class PlanFini: public PlanInfini{
	private:
//-------------------------Attributs------------------------------------
//----------------------------------------------------------------------
		const Vecteur longueur_;
		const Vecteur largeur_;
		std::shared_ptr<PlanFini> CloneMe() const {return std::shared_ptr<PlanFini>(new PlanFini(*this));}
		bool couleur_;		//Pour svaoir si le plan est visible ou non.
	public:
//------------------------Constructeur----------------------------------
//----------------------------------------------------------------------
		PlanFini(const Vecteur& origine={0,0,0},//const Vecteur& normal={0,0,1},
		const Vecteur& longueur={1,0,0}, const Vecteur& largeur={0,1,0}, double alpha = 0.8, double mu = 0.01, bool c=true);
//------------------------getters---------------------------------------
//----------------------------------------------------------------------	
		//je rajoute cela dans plan(06.04.22)
		const Vecteur& getLongueur() const{return longueur_; }
		const Vecteur& getLargeur() const{return largeur_;}
		bool getCouleur() const{return couleur_;}
//------------------------Méthodes--------------------------------------	
//----------------------------------------------------------------------	
		const Vecteur point_plus_proche(const ObjetMobile& o) const;
		
//------------------------Surcharge-------------------------------------
//----------------------------------------------------------------------
		virtual void affiche(std::ostream& sortie) const override;
		std::shared_ptr<Obstacle> copie() const override{return CloneMe();}	
		virtual void dessine_sur(SupportADessin& support) const override
		{ support.dessine(*this); }
};


class Brique: public Obstacle{
	
	private:
//-------------------------Attributs------------------------------------
//----------------------------------------------------------------------
		const Vecteur longueur_;
		Vecteur largeur_;
		double hauteur_;
		std::shared_ptr<Brique> CloneMe() const {return std::shared_ptr<Brique>(new Brique(*this));}
		bool couleur_;
	public:
//------------------------Constructeur----------------------------------
//----------------------------------------------------------------------
		Brique(const Vecteur& origine={0,0,0}, //const Vecteur& normal={0,0,1}, 
		const Vecteur& longueur={1,0,0}, const Vecteur& largeur={0,1,0}, double hauteur=0, double alpha = 0.8, double mu = 0.01, bool couleur=true);
//------------------------getters---------------------------------------
//----------------------------------------------------------------------
		const Vecteur& getLongueur() const{return longueur_;}
		const Vecteur& getLargeur() const{return largeur_;}
		double getHauteur() const{return hauteur_;}
		bool getCouleur() const{return couleur_;}
//------------------------Méthodes--------------------------------------
//----------------------------------------------------------------------		
		const Vecteur point_plus_proche(const ObjetMobile& o) const override;
		std::shared_ptr<Obstacle> copie() const override{return CloneMe();}
		virtual void dessine_sur(SupportADessin& support) const override
		{ support.dessine(*this); }
//------------------------Surcharge-------------------------------------
//----------------------------------------------------------------------		
		virtual void affiche(std::ostream& sortie) const override;
};

class Sphere: public Obstacle{
	public:
		Sphere(const Vecteur& position={0,0,0}, double rayon=1.0, double alpha = 0.8, double mu = 0.01);
		const Vecteur point_plus_proche(const ObjetMobile& o) const override;
		double getRayon() const{return rayon_;}
		void affiche(std::ostream& sortie) const override;
		std::shared_ptr<Obstacle> copie() const override{return CloneMe();}
		virtual void dessine_sur(SupportADessin& support) const override
		{ support.dessine(*this); }
	private:
		std::shared_ptr<Sphere> CloneMe() const {return std::shared_ptr<Sphere>(new Sphere(*this));}
		double rayon_;
};
//----------------------------------------------------------------------
class Terrain: public Obstacle{
	public:
	 Terrain(std::string f_d, std::string f_p,double scale=1.0, double t_x=0.0, double t_y=0.0, double t_z=0.0, 
		     double v_max=1.0, double range=1.0, double scaleZ=1.0,unsigned int div=60, std::vector<Vecteur> points_dessin={});
//------------------------getters---------------------------------------
//----------------------------------------------------------------------	 
	 std::string getNom() const{return f_points_;}
	 std::string getDessin() const{return f_dessin_;}
	 double getScale() const{return scale_;}
	 double getTransX() const{return trans_x;}
	 double getTransY() const{return trans_y;}
	 double getTransZ() const{return trans_z;}
	 double getVmax() const{return v_max_;}
	 double getRange() const{return range_;}
	 double getScaleZ() const{return scaleZ_;}
	 std::vector<Vecteur> getPointsDessin() const{return points_dessin_;}
	 unsigned int getDivision() const{return div_;}
//------------------------Méthodes--------------------------------------
//----------------------------------------------------------------------
	 virtual void agit_sur(ObjetMobile& o, const Integrateur& I, double dt = 0.01) const override;
	 virtual const Vecteur point_plus_proche(const ObjetMobile& o) const override;
	 std::vector<Vecteur> N_plus_proches(const ObjetMobile& o) const;
	 virtual void affiche(std::ostream& sortie) const override;
	 //~ virtual double distance(const ObjetMobile& o) const override;
	 std::shared_ptr<Obstacle> copie() const override{return CloneMe();}
		
	 virtual void dessine_sur(SupportADessin& support) const override
		{ support.dessine(*this); }
	
	private:
	std::shared_ptr<Terrain> CloneMe() const {return std::shared_ptr<Terrain>(new Terrain(*this));}
//f_points_ contient moins de points pour ere moins demandenat en calculs
	std::string f_dessin_;
	std::string f_points_;
	double scale_;
	double trans_x;double trans_y;double trans_z;
	double v_max_; double range_; //utile pour dessiner le gradient de couleur plus tard
	double scaleZ_; //Souvent les données sont un peu applaties dons on rajoute un agrandissement vertical
	unsigned int div_;
	std::vector<Vecteur> points_dessin_;
};
