/*#include <iostream>
#include "Vecteur.h"

using namespace std;
//L'idée de ces fonctions affiches est simplement d'afficher les vecteurs et leurs résultats
//Elles ne doivent donc pas utiliser les méthodes à l'intérieurs, le résultats sera donné en arguments.
//Convention pour les arguments :
//Opérande1, Opérande2, ..., Résultats, Opération.

void affiche(const Vecteur& vect1, const Vecteur& vect2, const Vecteur& resultat, operation op){
	vect1.affiche();
	if (op == add) cout << " + ";
	else if (op == sous) cout << " - ";
	else if (op == prod_vect) cout << " ^ ";
	else { cout << " Erreur : opération non trouvée" << endl;
		// il faudra créer une classe message d'erreur.
		return; 
		 } 
	vect2.affiche();
	cout << " = ";
	resultat.affiche();
	cout << endl;
}
void affiche(double x, const Vecteur& vect, const Vecteur& resultat, operation op){
	if (op == mult) cout << x << " * ";
	
	else{cout << " Erreur : opération non trouvée" << endl; return;} 
	
	vect.affiche();
	cout << " = "; 
	resultat.affiche();
	cout << endl;
}
void affiche(const Vecteur& vect, double x, const Vecteur& resultat, operation op){
	if (op == mult) vect.affiche();
	else{cout << " Erreur : opération non trouvée" << endl; return;}
	
	cout << " * " << x << " = ";
	resultat.affiche();
	cout << endl;
}
void affiche(const Vecteur& vect, double x, operation op){
	if (op == norme or op == norme2) cout << "||";
	
	else{cout <<  " Erreur : opération non trouvée" << endl; return;}
	
	vect.affiche();
	cout << "||";
	if (op == norme2) cout << "^2";
	cout << " = "<< x << endl;
}
void affiche(const Vecteur& vect1, const Vecteur& vect2, double resultat, operation op){
	if (op != prod_scal){ cout <<  " Erreur : opération non trouvée" << endl; return;}
	
	else{vect1.affiche();
		 cout << " * ";
		 vect2.affiche();
		 cout << " = " << resultat << endl;
		}
}
void affiche(const Vecteur& vect, const Vecteur& resultat, operation op){
	if (op != unit){cout <<  " Erreur : opération non trouvée" << endl; return;}
	
	vect.affiche();
	cout << " / ||";
	vect.affiche();
	cout << "|| = ";
	resultat.affiche();
	cout << endl;
}*/
