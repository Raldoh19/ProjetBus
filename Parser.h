#pragma once
#include "Vehicule.h"
#include "ListePlaces.h"
#include "Mission.h"
#include "Date.h"

#include <string>
using namespace std;

class Parser
{
private:
	string file;
public:
	Parser(string);
	ListePlaces * generateParking(vector<Mission>, vector<Vehicule*>);
	void generateTrajet(ListePlaces);
	vector<Vehicule*> generateVehicules();
	vector<Mission> generateMissions();
};

