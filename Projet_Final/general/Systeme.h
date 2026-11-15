#pragma once
#include <iostream>
#include <vector>
#include "support_a_dessin.h"
#include "Dessinable.h"
#include "Integrateur.h"
#include "ChampForces.h"
#include "constantes.h"
#include "ObjetCompose.h"
#include <memory>
class Systeme : public Dessinable{

	private:
		std::vector<std::shared_ptr<const Dessinable>> Dessins_;
		std::vector<std::shared_ptr<ObjetMobile>> Objets_;
		std::vector<std::shared_ptr<Obstacle>> Obstacles_;
		std::vector<std::shared_ptr<ChampForces>> Champs_; 
		double temps_;	//Sera utile pour certain dessin
		void ajoute_dessin(std::shared_ptr<const Dessinable> D);
		void ajoute_champ(std::shared_ptr<ChampForces> C);
		void ajoute_obstacle(std::shared_ptr<Obstacle> O);
		void ajoute_objet(std::shared_ptr<ObjetMobile> O);
		const std::vector<std::shared_ptr<ObjetMobile>>& getListeObjets() const{return Objets_;} 
		const std::vector<std::shared_ptr<Obstacle>>& getListeObstacles() const{return Obstacles_;}
		const std::vector<std::shared_ptr<ChampForces>>& getListeChamps() const{return Champs_;}
		friend void ObjetMobile::ajoute(Systeme&) const;
		friend void Obstacle::ajoute(Systeme&) const;
		friend void ChampForces::ajoute(Systeme&) const;
		friend void ObjetCompose::ajoute(Systeme&) const;
	public:
		Systeme():temps_(0.0){}
		Systeme& operator=(const Systeme&) = delete;
		Systeme(const Systeme&) = delete;
		
		const std::vector<std::shared_ptr<const Dessinable>>& getListeDessins() const{return Dessins_;}
		void affiche(std::ostream& sortie) const;
		void evolue(Integrateur& I, unsigned int n, double dt = 0.01);
		const double Temps() const {return temps_;}
		virtual void dessine_sur(SupportADessin& support) const override
		{ support.dessine(*this); }
		// [PERF] Réinitialise le système pour permettre le redémarrage de la simulation
		void reset() { Dessins_.clear(); Objets_.clear(); Obstacles_.clear(); Champs_.clear(); temps_ = 0.0; }
		~Systeme() = default;
};

std::ostream& operator<<(std::ostream& sortie, const Systeme&);
