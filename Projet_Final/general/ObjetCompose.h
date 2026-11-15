#pragma once 
#include <iostream>
#include "Dessinable.h"
#include "support_a_dessin.h"
#include "ObjetMobile.h"
#include "Obstacle.h"
#include "ChampForces.h"
#include <vector>
#include <memory>

struct ListeComposante{
	std::vector<std::shared_ptr<ObjetMobile>> Mobiles;
	std::vector<std::shared_ptr<Obstacle>>    Fixes;
	std::vector<std::shared_ptr<ChampForces>> Champs;
};
class ObjetCompose : public Dessinable{
	protected:
		ListeComposante L;
		const ListeComposante& getComposantes() const {return L;}
	public: 
		virtual void ajoute(Systeme& S) const;
		virtual std::shared_ptr<ObjetCompose> copie() const = 0;
		virtual ~ObjetCompose() = default;
};

class Ventilateur : public ObjetCompose{
	private:
		std::shared_ptr<Brique> brique_;
		std::shared_ptr<Vent> vent_;
	public:
		Ventilateur(const Vent& V, double h_brique);
		virtual void dessine_sur(SupportADessin& support) const override{support.dessine(*this);}	
		std::shared_ptr<ObjetCompose> copie() const override;
		Vent getVent() const {return *vent_;}
		Brique getBrique() const {return *brique_;}
};
