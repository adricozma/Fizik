#include <iostream> 
#include <fstream>
#include <string>
#include <cmath>
#include "../general/Erreur.h"
using namespace std;

void conversion_ll_xy(string fichier_entree, string fichier_sortie,double lat_debut,double long_debut,double lat_centre);
int main(){
	//Fichier contenat les valeurs de latitude,longitude, altitude
	string f_entree("data_non_projete/HeightData_K2.txt"); //Exemple ici pour le K2
	
	//Nouvoueau fichier contenant les coordonnées cartésiennes
	string f_sortie("HeightData_K2_ceciestuntest.txt"); 
	
//valeur de latitude/longitude au debut/centre de la carte, spécifique à chaque liste de points
	double lat_centre(35.888875333333); //Exemple ici pour le K2
	double lat_debut(35.844167);
	double long_debut(76.445833);
	conversion_ll_xy(f_entree,f_sortie,lat_debut,long_debut,lat_centre);
	return 0;
}
void conversion_ll_xy(string fichier_entree, string fichier_sortie,double lat_debut,double long_debut,double lat_centre){
	ifstream entree(fichier_entree);
	ofstream sortie(fichier_sortie,ios::out|ios::app);
	
	if((entree.fail() or sortie.fail())) throw Erreur("conversion_ll_xy()","Ouverture de fichier impossible");
		
		string element1;
		string element2;
		string element3;
		
	//l'axe des x sera representé par les longitudes
	//l'axe des y sera représenté par les latitudes
	
		double p(M_PI/180);					//conversion degrès->radian
		
		//constante pour la projection proche du centre de la carte
		double cfi0 (cos(lat_centre*p)); 
		int rayon(63781370);//Rayayon de la terre en m
		while(entree>>element1>>element2>>element3){
			if(!(entree.eof())){
				double lat(stod(element1)-lat_debut); double lon(stod(element2)-long_debut);
				double x(rayon*(lon*p)*cfi0/10); double y(rayon*lat*p/10);
				sortie<<x<<" "<<y<<" "<<element3<<endl;
			}
		}
		entree.close();
		sortie.close();
	
}
