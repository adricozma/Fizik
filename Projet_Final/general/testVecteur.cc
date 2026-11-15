#include <iostream>
#include <vector>
#include <initializer_list>
#include "Vecteur.h"
#include "constantes.h"
//#include "affiche.h"
using namespace std;

int main()
{
	Vecteur vect1;
	Vecteur vect2;
	Vecteur vect3;
	
	/* Cette partie
* (1) pourrait être écrite autrement, par exemple avec des
* manipulateurs (set_coord()) ;
* (2) sera revue dans 2 semaines (constructeurs, surcharge des opérateurs).
*/
//=========================test initialisation==========================
// v1 = (1.0, 2.0, -0.1)
//vect1.augmente(1.0); vect1.augmente(2.0); vect1.augmente(-0.1); vect1.augmente(-0.1);
//vect1.set_coord(1, 2.0); // pour tester set_coord()
// v2 = (2.6, 3.5, 4.1)
vect2.augmente(2.6); vect2.augmente(3.5); vect2.augmente(4.1);
//vect3 = vect1;

cout << "Vecteur 1 : ";
//vect1.affiche();
cout << vect1;
cout << endl;
cout << "Vecteur 2 : ";
cout << vect2;
cout << "Vecteur 3 : ";
cout << vect3;
//vect2.affiche();
cout << endl;
cout << "Le vecteur 1 est ";
if (vect1 == vect2) {
cout << "égal au";
} else {
cout << "différent du";
}
cout << " vecteur 2," << endl << "et est ";
if (vect1 != vect3) {
cout << "différent du";
} else {
cout << "égal au";
}
cout << " vecteur 3." << endl;
//=====================test operation===================================
	/*Vecteur vect_add;
	Vecteur	vect_opp;
	Vecteur	vect_sous;*/
	
	
/*cout << "addition test : v1 + v1" << endl;
vect_add = vect1.addition(vect2);
vect_add.affiche();
cout << endl << "oppose test : v1" << endl;
vect_opp = vect1.oppose();
vect_opp.affiche();
cout << endl << "soustraction test : v1 - v1" << endl;
vect_sous = vect1.soustraction(vect1);
vect_sous.affiche();
vect_sous.set_coord(1,2);
cout << endl;
vect_sous.affiche();*/
//======================================================================

/*affiche(vect1, vect2, vect1.addition(vect2), add);
affiche(vect1, vect2, vect1.soustraction(vect2), sous);
//affiche(vect1, vect2, vect1.prod_scal(vect2), prod_scal);
affiche(vect1, vect2, vect1.prod_vect(vect2), prod_vect);
affiche(3, vect1, vect1.mult(3), mult);
affiche(vect1, vect1.norme(), norme);
affiche(vect1, vect1.norme2(), norme2);
affiche(vect1, vect1.unitaire(), unit);*/
//=========================test constructeurs===========================
Vecteur v1, v2(2), v3(5), v4(3, 2.3, -0.2), v5({1,2,3,4}), v6(5,0,0);

cout << "v1 = " << v1 << endl;
cout << "v2 = " << v2 << endl;
cout << "v3 = " << v3 << endl;
cout << "v4 = " << v4 << endl;
cout << "v5 = " << v5 << endl;
//=========================test de la surcharge=========================
cout << " Test des surcharges d'opérateurs : " << endl;

/*affiche(vect1, vect2, vect1 + vect2, add);
affiche(vect1, vect2, vect1 - vect2, sous);
affiche(vect1, vect2, (vect1 + vect2) + vect2, add);*/
//=========================test Surcharge===============================

cout << vect1 << " + " << vect2 << " = " << vect1 + vect2 << endl;
cout << vect1 << " - " << vect2 << " = " << vect1 - vect2 << endl;
cout << vect1 << " * " << vect2 << " = " << vect1 * vect2 << endl;
//cout << vect1 << " ^ " << vect2 << " = " << (vect1 ^ vect2) << endl;
cout << vect1 << " * " <<   2   << " = " << vect1 * 2 << endl;
cout << vect2 << endl;
cout << vect1 << endl;
vect1 += vect2;
cout << vect2 << endl;
vect1 -= vect2;
cout << vect2 << endl;
//vect1 *= 2;
cout << vect1 << endl;
cout << vect2 << endl;
cout << " ~" << v6 << " = " << ~v6 << endl;
//======================================================================
//=======================test références================================
cout << endl << " Test références " << endl;
Vecteur r1(1,2,3);
cout << "r1 = " << r1 << endl;
Vecteur& r2(r1);
cout << "r2 = " << r2 << endl;
r2 *= 2.0;
cout << "r2 = " << r2 << endl;
cout << "r1 = " << r1 << endl;
// simple révision sur les références pour pouvoir simplifier l'écriture du code (renomer un "getter") 
// sans perdre en efficacité.
Vecteur k(2.6,3.5,4.1);
cout << k << endl;
cout << k.norme2() << endl;
cout << k.norme() << endl;

cout << ~g;
	return 0;
}

	
















