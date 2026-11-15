#pragma once
#include <iostream>
#include "Vecteur.h"
//#include "Obstacle.h"
#include "Dessinable.h"
#include "support_a_dessin.h"
#include "Erreur.h"
#include <memory>
//Déclaration de la classe ObjetMobile ainsi que des sous-classe qui lui sont associées
class Obstacle;
class Integrateur;
class Systeme;
class ObjetMobile : public Dessinable{
	public:
//================Constructeurs===================================//	
	ObjetMobile(double masse=1.0, double rayon=1.0, double alpha = 0.8, double mu = 0.01, 
		const Vecteur& p={0,0,0}, const Vecteur& v={0,0,0},
		const Vecteur& O={0,0,0}, const Vecteur& d={1,0,0});
	virtual ~ObjetMobile() = default;
//================Setters=========================================//	
	void setParam(const Vecteur& p){param_=p;}
	void setDparam(const Vecteur& d_p){d_param_=d_p;}
	virtual void setPosition(const Vecteur& p){return;} 
	//La méthode Setposition sera utile pour corriger un aspect technique de la simulation.
	//Elle permetra d'éviter à une balle qui "roule" sur un obstacle (plan par exemple) de passer au travers
	virtual void setVitesse(const Vecteur& v) = 0;
	virtual void setP_angulaire(const Vecteur& P){return;} //seule les objets à six degrés de liberté auront besoin de ces deux méthodes
	virtual void setV_angulaire(const Vecteur& V){return;}
	virtual const Vecteur getP_angulaire() const {return Vecteur(3);}
	virtual const Vecteur getV_angulaire() const {return Vecteur(3);}
//================Getters=========================================//	
	const Vecteur& getParam()					const{return param_;}
	const Vecteur& getDparam() 					const{return d_param_;}
	const double getRayon() 					const{return rayon_;}
	const double getMasse() 					const{return masse_;}
	const double getMasseVolumique() 			const;
	const Vecteur& getDirection() 				const{return direction_;}
	const Vecteur& getOrigine() 				const{return origine_;}
	const Vecteur& getForce() 					const{return force_;}
	virtual const Vecteur getResultanteForce() 	const = 0;
	virtual const Vecteur getPosition() 		const = 0;
	virtual const Vecteur getVitesse()			const = 0;
	const double getAlpha() 					const{return alpha_;}
	const double getMu()						const{return mu_;}
//================Méthodes========================================//		
	void reset_force();
	virtual const Vecteur evolution() 							const = 0;
	virtual void ajoute_force(Vecteur const& df){force_+=df;}
	virtual void affiche(std::ostream& sortie) 					const = 0;
	const double distance(const ObjetMobile& o) 				const;
	void agit_sur(ObjetMobile& o, const Integrateur& I, double dt = 0.01);
	bool choc(const ObjetMobile& o) 							const;
	bool choc(const Obstacle& o) const;
	virtual std::shared_ptr<ObjetMobile> copie()				const = 0;
	void ajoute(Systeme& S) 									const;
//================Attributs=======================================//	
	protected:
	Vecteur param_;
	Vecteur d_param_;
	Vecteur direction_;
	Vecteur origine_;
	Vecteur force_;
	const double rayon_;
	//const double masse_volumique_;
	const double masse_;
	double alpha_;
	double mu_;
};
//================Surcharge=======================================//

std::ostream& operator<<(std::ostream& sortie, ObjetMobile const& o);

//================================================================//

class Pendule: public ObjetMobile{
	private:
		
		double longueur_;
		double b_;  //coefficient de frottement
		std::shared_ptr<Pendule> CloneMe() const {return std::shared_ptr<Pendule>(new Pendule(*this));}
	public: 
		Pendule(double massse = 1.0, double rayon = 1.0, double alpha = 0.8, double mu = 0.01, double longueur = 1.0, double b = 0.0, const Vecteur& p={0}, 
				const Vecteur& v = {0}, const Vecteur& O = {0,0,0},
				const Vecteur& d = {0,0,0});

//======================================================================
//==========================setters=====================================
		void setPosition(const Vecteur& p) override;
		void setVitesse(const Vecteur& v) override;
//======================================================================
//========================Accesseurs====================================	
		const double getLongueur()           const{return longueur_;}
		const double getFrottement()         const{return b_;}		
//======================================================================
//==========================Méthodes====================================			
		const Vecteur evolution()            const override;
		const Vecteur getPosition()          const override;
		const Vecteur getVitesse()           const override;
		const Vecteur getResultanteForce()   const override;
		const Vecteur u_theta() 		     const;        //Utile pour setPosition() et setVitesse()
		std::shared_ptr<ObjetMobile> copie() const override {return CloneMe();}
		
		virtual void dessine_sur(SupportADessin& support) const override{support.dessine(*this);}
		void affiche(std::ostream& sortie) const override;
};
class Balle: public ObjetMobile {
	private:
		std::shared_ptr<Balle> CloneMe() const {return std::shared_ptr<Balle>(new Balle(*this));}
	public: 
//=======================Constructeur==============================//
		 Balle(double masse = 1.0, double rayon=1.0, double alpha = 0.8, double mu = 0.01, 
		 const Vecteur& p={0,0,0}, const Vecteur& v={0,0,0});
//par défaut les Vecteurs sont initialisès à la position (0.0.0) c'est un choix de notre part	

//======================Getters====================================//
		const Vecteur getPosition()        const override {return getParam();}
		const Vecteur getVitesse()         const override {return getDparam();}
		const Vecteur getResultanteForce() const override {return getForce();}	
//======================Setters====================================//
		void setPosition(const Vecteur& p) override	{setParam(p);}
		void setVitesse(const Vecteur& v)  override {setDparam(v);}
//======================méthodes===================================//
		const Vecteur evolution()                const override;
		virtual void ajoute_force(const Vecteur& df)   override;
		std::shared_ptr<ObjetMobile> copie()     const override {return CloneMe();}
		void affiche(std::ostream& sortie)       const override;
		virtual void dessine_sur(SupportADessin& support) const override{support.dessine(*this);}
};

class Caillou : public Balle{
	private:
		std::shared_ptr<Caillou> CloneMe() const {return std::shared_ptr<Caillou>(new Caillou(*this));}
	public:
		using Balle::Balle;
		void ajoute_force(const Vecteur& df) override {ObjetMobile::ajoute_force(df);}
		std::shared_ptr<ObjetMobile> copie()     const override {return CloneMe();}
		//~ void affiche(std::ostream& sortie)       const override;
};

class Boulet : public ObjetMobile{
	private:
		std::shared_ptr<Boulet> CloneMe() const {return std::shared_ptr<Boulet>(new Boulet(*this));}
	public:
		Boulet(double masse = 1.0, double rayon=1.0, double alpha = 0.8, double mu = 0.01,
			   Vecteur p={0,0,0}, const Vecteur& p_ang = {0,0,0}, Vecteur v={0,0,0}, const Vecteur& v_ang = {0,0,0});
		void setPosition(const Vecteur& P)			override;
		void setVitesse(const Vecteur& V)			override;
		void setP_angulaire(const Vecteur& P)		override;
		void setV_angulaire(const Vecteur& V)		override;
		const Vecteur getPosition() 		  const override;
		const Vecteur getVitesse()			  const override;
		const Vecteur getP_angulaire()		  const override;
		const Vecteur getV_angulaire() 		  const override;
		const Vecteur evolution()			  const override;
		const Vecteur getResultanteForce() 	  const override {return getForce();}	
		virtual void dessine_sur(SupportADessin& support) const override{support.dessine(*this);}
		std::shared_ptr<ObjetMobile> copie()  const override {return CloneMe();}
		void affiche(std::ostream& sortie)	  const override;
};	
class Ressort : public ObjetMobile{
	
	private:
		const double k_;				//Raideur du ressort
		const double longueur_a_vide_;	//Longueur à vide du ressort
		const double b_;      			//coefficient de frottement
		std::shared_ptr<Ressort> CloneMe() const {return std::shared_ptr<Ressort>(new Ressort(*this));}
	public: 
		Ressort(double masse=1.0, double rayon=1.0, double alpha = 0.8, double mu = 0.01, 
		const Vecteur& p={0}, const Vecteur& v={0}, const Vecteur& O = {0,0,0},
		const Vecteur& d={0,0,1}, double k = 1.0, double b = 0.0, double longeur_a_vide = 0.0);
		
		//~ void setPosition(const Vecteur& p) 			override{setParam(p.Projection(getDirection()));}
		void setVitesse(const Vecteur& v)			override;
		
		const double getRaideur()			  const{return k_;}
		const double getLongueur()			  const{return longueur_a_vide_;}
		const double getFrottement()		  const{return b_;}
		const Vecteur getAttache()			  const;
		const Vecteur getResultanteForce()	  const override;	
		
		const Vecteur evolution()             const override;
		const Vecteur getPosition()           const override;
		const Vecteur getVitesse()            const override;
		std::shared_ptr<ObjetMobile> copie()  const override {return CloneMe();}
		void affiche(std::ostream& sortie)    const override;
		virtual void dessine_sur(SupportADessin& support) const override{support.dessine(*this);}	
};
class PenduleSpherique : public ObjetMobile{
	private: 
		double longueur_;
		std::shared_ptr<PenduleSpherique> CloneMe() const {return std::shared_ptr<PenduleSpherique>(new PenduleSpherique(*this));}
	public: 
		PenduleSpherique(double masse=1.0, double rayon=0.0, double alpha = 0.8, double mu = 0.01,
		double longueur = 1.0, const Vecteur& p={0,0}, const Vecteur& v={0,0}, const Vecteur& O={0,0,0},
		const Vecteur& d={0,0,0});
		
		//~ void setPosition(const Vecteur& p) override;
		void setVitesse(const Vecteur& v)  override;
		
		const double getLongueur()          const {return longueur_;}
			
		const Vecteur evolution()           const override;
		const Vecteur getPosition()         const override;
		const Vecteur getVitesse()          const override;
		const Vecteur getResultanteForce()  const override;
		std::shared_ptr<ObjetMobile> copie()const override {return CloneMe();}
		void affiche(std::ostream& sortie)  const override;
		virtual void dessine_sur(SupportADessin& support) const override{support.dessine(*this);}	
};









