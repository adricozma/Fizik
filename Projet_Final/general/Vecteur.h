#pragma once
#include <vector>
#include <iostream>
#include <initializer_list>
typedef std::vector<double> Vect;

//enum operation{comp, add, sous, mult, prod_scal, norme, norme2, prod_vect, unit};

class Vecteur
{
	private:
	
	Vect vecteur_;

	double getCoord(std::size_t);
//modularisation
	 		
//=========================boîte à outils===============================

	Vecteur same_di(std::size_t dim_ajout) const;
//======================================================================
	
	public:
	
//=========================Constructeur=================================
//======================================================================
	
	//Vecteur() = default;
	Vecteur(std::size_t dim = 0);
	Vecteur(double x, double y, double z);
	Vecteur(const std::initializer_list<double>& liste);
	
	//==================================================================
//=======================Méthode outils=================================
//======================================================================
	std::size_t getSize() const{return getVecteur().size();}
//getSize() sert modulariser le code
	void affiche() const;
	const Vect& getVecteur() const {return vecteur_;}
// L'accesseur renvoie une référence constante sur l'attribut pour éviter les copies inutiles.
	void augmente(double valeur);
	Vecteur augmente(const Vecteur& v);
	void set_coord(std::size_t pos, double val);         
//On prend la convention que la première position est de coordonnée
//1 et non 0.
	Vecteur oppose() const;
	double norme()  const;
	double norme2() const;
	const Vecteur Projection(const Vecteur& v) const;
//a.Projection(b) retourne la projection de a sur b.
//======================================================================
//====================Surcharge interne=================================
//======================================================================
	bool operator==(const Vecteur& v_comp) const;
	bool operator!=(const Vecteur& v_comp) const;
	Vecteur& operator+=(const Vecteur& v_add);
	Vecteur& operator-=(const Vecteur& v_sous);
	Vecteur& operator*=(double x);
	const double operator*(const Vecteur& v_prodscal) const;
	Vecteur& operator^=(const Vecteur& v_prodvect);
	const Vecteur operator~() const;
	
};
//======================================================================
//=====================Surcharge externes===============================
//======================================================================
std::ostream& operator<<(std::ostream& sortie, const Vecteur& vect);

const Vecteur operator+(Vecteur vect1, const Vecteur& vect2);
	
const Vecteur operator-(Vecteur vect1, const Vecteur& vect2);
	
const Vecteur operator*(double x, Vecteur vect);
	
const Vecteur operator*(Vecteur vect, double x);
	
const Vecteur operator^(Vecteur vect1, const Vecteur& vect2);




