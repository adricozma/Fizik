#pragma once
#include <iostream>
//#include "Vecteur.h"
#include "ObjetMobile.h"
#include "Obstacle.h"
#include <memory>
class Systeme;
class ChampForces{
	
	protected:
		Vecteur intensite_;
		std::shared_ptr<ChampForces> CloneMe() const {return std::shared_ptr<ChampForces>(new ChampForces(*this));}
//===============================================================//		
	public:
//=================Constructeur==================================//
		ChampForces(const Vecteur& intensite);
		virtual std::shared_ptr<ChampForces> copie() const {return CloneMe();}
//====================Méthode====================================//		
		virtual void agit_sur(ObjetMobile& o) const;
		Vecteur getIntensite() const{return intensite_;}
		virtual void ajoute(Systeme& S) const;
		virtual void affiche(std::ostream& sortie) const;
		virtual ~ChampForces() = default;
};
class Vent : public ChampForces{
	private: 
		Vecteur origine_;
		Vecteur normal_;
		Vecteur longueur_;
		Vecteur largeur_;
		double profondeur_;    //La profondeur est le long du vecteur normal_ 
		double V0_;
		bool dedans(const ObjetMobile& O) const;
		std::shared_ptr<Vent> CloneMe() const {return std::shared_ptr<Vent>(new Vent(*this));}
	public:	
		Vent(const Vecteur& origine, const Vecteur& longueur, const Vecteur& largeur, double profondeur, double V0);
		void agit_sur(ObjetMobile& O) const override;
		const Vecteur& getOrigine() const{return origine_;}
		const Vecteur& getNormal() const{return normal_;}
		const Vecteur& getLongueur() const{return longueur_;}
		const Vecteur& getLargeur() const{return largeur_;} 
		const double getProfondeur() const{return profondeur_;}
		std::shared_ptr<ChampForces> copie() const override{return CloneMe();}
		void affiche(std::ostream& sortie) const override;
};
//==================Opérateur====================================//
std::ostream& operator<<(std::ostream& sortie, ChampForces const& c);	
