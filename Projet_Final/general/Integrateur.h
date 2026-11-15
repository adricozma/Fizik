#pragma once
#include <iostream>

class ObjetMobile;

class Integrateur{	
	public:
		virtual void evolue(ObjetMobile& O, double dt = 0.01) const;
// pas de méthode virtuelle pure ici pour laisser la posibilité de créer un intégrateur "classique"
};

class IntegrateurEulerCromer : public Integrateur{	
	public:
		void evolue(ObjetMobile& O, double dt = 0.01) const override;
};

class IntegrateurRungeKutta : public Integrateur{
	public:
		void evolue(ObjetMobile& O, double dt = 0.01) const override;
};

