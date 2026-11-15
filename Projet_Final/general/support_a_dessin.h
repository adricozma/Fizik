#pragma once

//class ObjetMobile;
//class Obstacle
class Balle;
class Pendule;
class PenduleSpherique;
class Ressort;
class PlanFini;
class PlanInfini;
class Brique;
class Sphere;
class Terrain;
class Systeme;
class Ventilateur;
class Boulet;
class Caillou;

class SupportADessin
{
 public:
  virtual ~SupportADessin() = default;
  // on ne copie pas les Supports
  SupportADessin(SupportADessin const&)            = delete; 
  SupportADessin& operator=(SupportADessin const&) = delete;
   // mais on peut les déplacer
  SupportADessin(SupportADessin&&)            = default; 
  SupportADessin& operator=(SupportADessin&&) = default;
  
  SupportADessin() = default; 

  //virtual void dessine(ObjetMobile const& a_dessiner) = 0;
  //virtual void dessine(Obstacle const& a_dessiner) = 0;
  
  virtual void dessine(Balle const& a_dessiner) = 0;
  virtual void dessine(Pendule const& a_dessiner) = 0;
  virtual void dessine(PenduleSpherique const& a_dessiner) = 0;
  virtual void dessine(Ressort const& a_dessiner) = 0;
  virtual void dessine(PlanInfini const& a_dessiner) = 0;
  virtual void dessine(PlanFini const& a_dessiner) = 0;
  virtual void dessine(Brique const& a_dessiner) = 0;
  virtual void dessine(Sphere const& a_dessiner) = 0;
  virtual void dessine(Terrain const& a_dessiner) = 0;
  virtual void dessine(Systeme const& a_dessiner) = 0;
  virtual void dessine(Ventilateur const& a_dessiner) = 0;
  virtual void dessine(Boulet const& a_dessiner) = 0;
};

class TextViewer : public SupportADessin{
	public:
		TextViewer(std::ostream& flot)
		: flot(flot)
		{}
		void dessine(Balle const& a_dessiner)			override;
		void dessine(Pendule const& a_dessiner)			override;
		void dessine(PenduleSpherique const& a_dessiner)override;
		void dessine(Ressort const& a_dessiner)			override;
		void dessine(PlanInfini const& a_dessiner)		override;
		void dessine(PlanFini const& a_dessiner)		override;
		void dessine(Brique const& a_dessiner)			override;
		void dessine(Sphere const& a_dessiner)			override;
		void dessine(Terrain const& a_dessiner) 		override;
		void dessine(Systeme const& a_dessiner)			override;	
		void dessine(Ventilateur const& a_dessiner)		override;
		void dessine(Boulet const& a_dessiner)			override;
	private:
		std::ostream& flot;
};
