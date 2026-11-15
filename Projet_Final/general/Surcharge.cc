/*#include "vecteur.h"
#include <iostream>
using namespace std;

//========================Surcharge=====================================
ostream& operator<<(ostream& out, Vecteur vect){
	vect.affiche();
	return out;
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




const Vecteur operator+(Vecteur vect1, const Vecteur& vect2)
	{return vect1.addition(vect2);}
	
const Vecteur operator-(Vecteur vect1, const Vecteur& vect2)
	{return vect1.soustraction(vect2);}
	
const Vecteur operator*(double x, const Vecteur& vect)
	{return vect.mult(x);}
	
const Vecteur operator*(const Vecteur& vect, double x)
	{return vect.mult(x);}
	
const Vecteur operator*(Vecteur vect1, const Vecteur& vect2)
	{return vect1.prod_scal(vect2);}
	
const Vecteur operator^(Vecteur vect1, const Vecteur& vect2)
	{return vect1.prod_vect(vect2);}

Vecteur& Vecteur::operator+=(const Vecteur& vect){
	(*this) = addition(vect);
	return *this;
}*/
