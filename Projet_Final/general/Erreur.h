#pragma once
#include <iostream>
#include <string>

class Erreur{
	private:
		std::string origine_;		//lieu d'ou provient l'erreur
		const std::string type_;	//rapide description de l'erreur
	public:
		Erreur(const std::string origine, const std::string type)
		:origine_(origine), type_(type)
		{}
		void affiche(){std::cerr << "Erreur dans : " << origine_ << std::endl << "Type : " << type_;}
		void setChemin(const std::string& s){origine_ += (" -> " + s);}
};

