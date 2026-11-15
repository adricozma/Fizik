#include "terrain.h"
#include "vue_opengl.h"
#include <string>
using namespace std;

void Terrain::dessine(QMatrix4x4 point_de_vue, std::string fichier_entree){
	ifstream entree(fichier_entree);
	
	QMatrix4x4 matrice;
	
	if(!entree.fail()){
		string element1;
		string element2;
		string element3;
		while(entree>>element1>>element2>>element3){
			if(!(entree.eof())){
				double x(stod(element1)); double y(stod(element2)); double z(stod(element3));
				dessineCercle(point_de_vue, x,y,z,1,3);
			}
		}
		entree.close();

	}else{
		cerr<<" Impossible d'ouvrir les fichiers"<<endl;
	}
}
