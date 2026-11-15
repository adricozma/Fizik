#include "terrain.h"
#include "vue_opengl.h"
using namespace std;

void Terrain::dessine(string fichier_entree){//,double latitude_centre){
	ifstream entree(fichier_entree);
	
	QMatrix4x4 matrice;
	
	if(!entree.fail()){
		string element1;
		string element2;
		string element3;
		//int n(0);
		while(entree>>element1>>element2>>element3){
			if(!(entree.eof())){
				double x(stod(element1)); double x(stod(element2)); double z(stod(element3));
				dessineCercle(matrice, x,y,z,1,3);
			}
		}
		entree.close();

	}else{
		cerr<<" Impossible d'ouvrir les fichiers"<<endl;
	}
}
