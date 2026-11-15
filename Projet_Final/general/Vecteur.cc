#include <iostream>
#include <cmath>
#include <iomanip>
#include "Vecteur.h"
#include "constantes.h"
#include "Erreur.h"

using namespace std;


//=======================Définition constructeurs========================
Vecteur::Vecteur(size_t dim){
	while(dim > 0){ 
		vecteur_.push_back(0.0);
		--dim;
	}
}

Vecteur::Vecteur(double x, double y, double z)
{vecteur_.push_back(x); vecteur_.push_back(y); vecteur_.push_back(z);}

Vecteur::Vecteur(const initializer_list<double>& liste)
{for (auto element : liste) vecteur_.push_back(element);}
	
//=======================Définition méthodes============================
void Vecteur::augmente(double valeur = 0.0){
	vecteur_.push_back(valeur);											
//ATTENTION : ICI on ne peut pas utiliser la fonction getVecteur() car cette 
//fonction est de type const et ici on veut modifier les attributs.
// La donnée dit d'ajouter la valeur à la nouvelle dimension, donc un push_back() suffit.
}
Vecteur Vecteur::augmente(const Vecteur& v){
	Vecteur copie(*this);
	for(auto element : v.getVecteur()){
		copie.augmente(element);
	}
	return copie;
}
// On augmente la dimension de v1 en lui ajoutant les valeurs de v2
//======================================================================

void Vecteur::set_coord(size_t pos, double val){
//	if (...)
	vecteur_[pos - 1] = val;
} 
// gestion d'erreur
//======================================================================

/*void Vecteur::affiche() const{
	cout << "( ";
	for (auto element : getVecteur()) cout << element << " ";
	cout << ")";
}*/
//======================================================================

Vecteur Vecteur::same_di(size_t dim_ajout) const{
	Vecteur retour(*this);
	while (dim_ajout > 0){ 
		retour.augmente(0.0);
		--dim_ajout;
	}
	return retour;
	
}
//======================================================================
//=====================Méthode outils===================================
Vecteur Vecteur::oppose() const{ 
	return *this * -1;
}
//======================================================================
double Vecteur::norme()  const{
	return sqrt(norme2());
}
//======================================================================

double Vecteur::norme2() const{
	/*double norme_retour(0);
	for (auto element : getVecteur()) norme_retour += element * element;
	return norme_retour;*/
	return (*this)*(*this);
}
//======================================================================

const Vecteur Vecteur::Projection(const Vecteur& v) const{
	if (v == Vecteur(3)) throw Erreur("Vecteur nul","Vecteur::Projection()");
	return ((*this * v)/v.norme2())*v;	
}

//======================================================================
//=======================Surcharge interne==============================

bool Vecteur::operator==(const Vecteur& v_comp) const{
	if (getSize() != v_comp.getSize()) return false;
			
		for (size_t i(0); i < getSize(); ++i){
			if(abs(getVecteur()[i] - v_comp.getVecteur()[i]) > epsilon) return false;
			//compare chaque paire d'éléments avec epsilon.
		 }
	return true;
}
//Si aucun des tests ne réagit, c'est que les deux vecteurs sont égaux
//Si on compare deux vecteurs de dimension 0, alors le test retournera true
//======================================================================

bool Vecteur::operator!=(const Vecteur& v_comp) const{
	return not (*this == v_comp);
}
//======================================================================


Vecteur& Vecteur::operator+=(const Vecteur& v_add){
	if (getSize() > v_add.getSize()) return *this += v_add.same_di(getSize() - v_add.getSize());
	if (getSize() < v_add.getSize()){ 
	*this = (*this).same_di(v_add.getSize() - getSize());
	return *this += v_add;
	}
//On se permet de modifier les opérandes dans les cas limites.
//Exemple si on fait v1 += v2 et que v1 est plus petit, alors v1 sera modifié.
//Par contre, si v2 est plus petit, alors il restera inchangé. 
	for (size_t i(0); i < getSize(); ++i) vecteur_[i] = (getVecteur()[i] + v_add.getVecteur()[i]);
	
	return *this;
}
//======================================================================
Vecteur& Vecteur::operator-=(const Vecteur& v_sous){
	return *this += v_sous.oppose();
}
//======================================================================
Vecteur& Vecteur::operator*=(double x){
	for (auto& element : vecteur_) element *= x;
	return *this;
}
//======================================================================
const double Vecteur::operator*(const Vecteur& v_prodscal) const{
	double prod(0); 
	for (size_t i(0); i < min(getSize(), v_prodscal.getSize()); ++i){
		prod += getVecteur()[i] * v_prodscal.getVecteur()[i];
	}
	return prod;
// si on a un vecteur "vide", alors on retorne 0
}
//======================================================================
//======================================================================

Vecteur& Vecteur::operator^=(const Vecteur& v_prodvect) {
	if (getSize() != 3 or v_prodvect.getSize() != 3) throw(Erreur("operator^=", "Produit Vectoriel non défini"));
	Vecteur retour;
	retour.augmente(getVecteur()[1] * v_prodvect.getVecteur()[2] - getVecteur()[2] * v_prodvect.getVecteur()[1]);
	retour.augmente(getVecteur()[2] * v_prodvect.getVecteur()[0] - getVecteur()[0] * v_prodvect.getVecteur()[2]);
	retour.augmente(getVecteur()[0] * v_prodvect.getVecteur()[1] - getVecteur()[1] * v_prodvect.getVecteur()[0]);
	(*this) = retour;
	return *this;
// ICI, on est obligé de créer un vecteur retour et de faire une copie car les attributs
// de l'instance pointée par "this" sont modifiés au cours de la formule;
}
//======================================================================

const Vecteur Vecteur::operator~() const{
	if (norme() == 0) throw(Erreur("operator~", "Vecteur nul"));
//Cette erreur arrêtera le programme.
	return *this * (1/norme());
}
//======================Surcharge Externe===============================

ostream& operator<<(ostream& sortie, const Vecteur& vect){
	//~ sortie << "( ";
	for (auto element : vect.getVecteur()) sortie << setprecision(15) << element << " ";// << showpoint << fixed << element << " ";
	//~ sortie << ")";
	return sortie;
}
const Vecteur operator+(Vecteur v1, const Vecteur& v2)
{
return v1+=v2;	
}
	
const Vecteur operator-(Vecteur v1, const Vecteur& v2){
	return v1-=v2;
}

const Vecteur operator*(double x, Vecteur v){
	return v*=x;	
}
	
const Vecteur operator*(Vecteur v, double x){
	return v*=x;
}
	
const Vecteur operator^(Vecteur v1, const Vecteur& v2){
	return v1^=v2;
}

//======================================================================

