#include "ObjetCompose.h"
#include "Systeme.h"
using namespace std;

Ventilateur::Ventilateur(const Vent& V, double h_brique)
:vent_(shared_ptr<Vent>(new Vent(V))), brique_(shared_ptr<Brique>(new Brique(Brique(V.getOrigine(), V.getLongueur(), V.getLargeur(),1.0,0.00, h_brique))))
{
 L.Champs.push_back(vent_);
 L.Fixes.push_back(brique_);}
//On facilite l'accès avec les attributs donnés tel quel. Ils ajoutent une 
//copie de leur poiteur à la collection de composante

shared_ptr<ObjetCompose> Ventilateur::copie() const{
	shared_ptr<ObjetCompose> sh(new Ventilateur(*this));
	return sh;
}

void ObjetCompose::ajoute(Systeme& S) const{
	shared_ptr<ObjetCompose> OC(copie());
	S.ajoute_dessin(OC);
	for (const auto& element : OC->getComposantes().Mobiles){
		S.ajoute_objet(element);
	}
	for (const auto& element : OC->getComposantes().Fixes){
		S.ajoute_obstacle(element);
	}	
	for (const auto& element : OC->getComposantes().Champs){
		S.ajoute_champ(element);
	}				
//ne doit pas refaire une nouvelle copie des éléments ajouté car 
//le but est que les composantes restent liées à leur dessins.						
}
