#pragma once
#include "Vehicule.h"
#include "ListePlaces.h"
#include "Mission.h"
#include "Date.h"

#include <string>
using namespace std;

class Generateur
{
private:
	string file;
public:
	Generateur(string);
	void setFile(string);
	void generateVehicules(int nbVehicule);
	void generateMissions(int nbVehicule, Date dateDebut, Date dateFin);

	void generateParkingFile(ListePlaces parking);

	void generateParkingA(int nombrePlace, int nbColonne);
	void generateParkingB(int nombrePlace, int nbColonne);
	~Generateur(void);
	void generateParkingB5(int nbColonne);
	void generateParkingB10(int nbColonne);
};

