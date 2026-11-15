#include <iomanip>
#include "Systeme.h"
#include <vector>
#include "Integrateur.h"
#include "Erreur.h"
#include "Dessinable.h"
#include <memory>


using namespace std;

void Systeme::ajoute_dessin(shared_ptr<const Dessinable> D){
	if (D == nullptr) throw(Erreur("Systeme::ajoute_dessin", "nullptr"));
	Dessins_.push_back(D);
}
void Systeme::ajoute_champ(shared_ptr<ChampForces> C){
	if (C == nullptr) throw(Erreur("Systeme::ajoute_Champ", "nullptr"));
	Champs_.push_back(C);
}
void Systeme::ajoute_obstacle(shared_ptr<Obstacle> O){
	if (O == nullptr) throw(Erreur("Systeme::ajoute_obstacle", "nullptr"));
	Obstacles_.push_back(O);
}
void Systeme::ajoute_objet(shared_ptr<ObjetMobile> O){
	if (O == nullptr) throw(Erreur("Systeme::ajoute_objet", "nullptr"));
	Objets_.push_back(O);
}
void Systeme::affiche(ostream& sortie) const{
	sortie << "Le système est constitué de : " << endl;
	
	if(not getListeObjets().empty()){
		sortie << endl << "objets mobiles :" << endl << endl;
		for (const auto& element : getListeObjets()) sortie << *element << endl;
	}
	if(not getListeObstacles().empty()){
		sortie << endl << "obstacles :" << endl;
		for (const auto& element : getListeObstacles()) sortie << *element << endl;
	}
	if(not getListeChamps().empty()){
		sortie << endl << "champs de force :" << endl;
		for (const auto& element : getListeChamps()) sortie << *element << endl;
	}
}
ostream& operator<<(ostream& sortie, const Systeme& S){
	S.affiche(sortie);
	return sortie;
}

void Systeme::evolue(Integrateur& I, unsigned int n, double dt){
	if (getListeObjets().empty()) return;
	// s'il n'y a pas d'objets mobile, ça ne sert à rien de simuler un système vide.
	while (n > 0){
		//Première Boucle pour initialiser les forces s'appliquant à chaque objet
		for (auto& element : Objets_){
			(*element).reset_force();
			//On s'assure que les forces ont été remises à zéro avant de les recalculer
			for (const auto& C : Champs_){
				(*C).agit_sur(*element); 
			}
		}
		//Deuxième boucle pour calculer les chocs éventuels
		for (size_t i(0); i < getListeObjets().size(); ++i){
				for(size_t j(i+1); j < getListeObjets().size(); ++j){
				//Si la taille de la liste est 1, la deuxième boucle ne se lancera pas
					if((*Objets_[i]).choc(*Objets_[j])){
						//~ cout << "Avant choc :" << endl;
						//~ cout << "position 1 = " << (*Objets_[i]).getPosition() << endl;
						//~ cout << "position 2 = " << (*Objets_[j]).getPosition() << endl;
						//~ cout << "vitesse 1 = " << (*Objets_[i]).getVitesse() << endl;
						//~ cout << "vitesse 2 = " << (*Objets_[j]).getVitesse() << endl;
						//~ cout << "force 1 = " << (*Objets_[i]).getResultanteForce() << endl; 
						//~ cout << "force 2 = " << (*Objets_[j]).getResultanteForce() << endl;
						//~ cout << "BOOOOOOOOOOOOOMMMM" << endl;
						(*Objets_[i]).agit_sur(*Objets_[j], I, dt);
						//~ cout << "Après choc :" << endl;
						//~ cout << "position 1 = " << (*Objets_[i]).getPosition() << endl;
						//~ cout << "position 2 = " << (*Objets_[j]).getPosition() << endl;
						//~ cout << "vitesse 1 = " << (*Objets_[i]).getVitesse() << endl;
						//~ cout << "vitesse 2 = " << (*Objets_[j]).getVitesse() << endl;
						//~ cout << "force 1 = " << (*Objets_[i]).getResultanteForce() << endl; 
						//~ cout << "force 2 = " << (*Objets_[j]).getResultanteForce() << endl;
					}
				}
				for (auto& element : Obstacles_){
						if ((*Objets_[i]).choc(*element)){
							//~ cout << endl << "Avant rebond sol :" << endl << endl;
							//~ cout << "vitesse = " << (*Objets_[i]).getVitesse() << endl;
							//~ cout << "force = " << (*Objets_[i]).getResultanteForce() << endl;
							//~ cout << "PAAAAAAAAAAAAAAAFFFFFF" << endl;
							(*element).agit_sur(*Objets_[i],I,dt);
							//~ cout << endl << "Après rebond sol :" << endl << endl;
							//~ cout << "vitesse = " << (*Objets_[i]).getVitesse() << endl;
							//~ cout << "force = " << (*Objets_[i]).getResultanteForce() << endl;
						}
				}
		}
		//Troisième Boucle qui fait évoluer les objets
		for (auto& objets : Objets_){
			I.evolue(*objets,dt);
		}
		cout << endl;
		temps_+=dt;
		--n;
	}
}
