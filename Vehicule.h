#ifndef VEHICULE_H
#define VEHICULE_H

#include "Mission.h"
#include <vector>

class Vehicule
{
private:
	int ID;
	int tailleVehicule;
	std::vector<Mission> missions;
public:
	Vehicule(int id, int taille);
	~Vehicule();
	int getID();
	int getTailleVehicule();
	void setID(int id);
	void setTailleVehicule(int taille);
	void ajouterMission(Mission m);
	void retirerMission(Mission m);
	void afficherMissions();
	std::vector<Mission> getMissions();
	int getNbMissions();
};

#endif