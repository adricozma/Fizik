#include <iostream>
#include "Systeme.h"

using namespace std;

void TextViewer::dessine(Balle const& a_dessiner){flot << a_dessiner.getPosition() << " ";}
void TextViewer::dessine(Pendule const& a_dessiner){flot << a_dessiner.getPosition() << " ";}
void TextViewer::dessine(PenduleSpherique const& a_dessiner){flot << a_dessiner.getPosition() << " ";}
void TextViewer::dessine(Ressort const& a_dessiner){flot << a_dessiner.getPosition() << " ";}
void TextViewer::dessine(PlanInfini const& a_dessiner){flot<< "";}
void TextViewer::dessine(PlanFini const& a_dessiner){flot << "";}
void TextViewer::dessine(Brique const& a_dessiner){flot << "";}
void TextViewer::dessine(Sphere const& a_dessiner){flot<< "";}
void TextViewer::dessine(Ventilateur const& a_dessiner){flot  << "";}
void TextViewer::dessine(Systeme const& a_dessiner){for (const auto& element : a_dessiner.getListeDessins()) element->dessine_sur(*this); 
																			flot<<endl;}
void TextViewer::dessine(Terrain const& a_dessiner){flot << "";}
void TextViewer::dessine(Boulet const& a_dessiner){flot << a_dessiner.getPosition() << " ";}//<< a_dessiner.getP_angulaire() << " " 	
															//<< a_dessiner.getVitesse() << " " << a_dessiner.getV_angulaire() << " ";}
