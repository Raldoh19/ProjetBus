// ProjetBus.cpp : définit le point d'entrée pour l'application console.
//

#include <iostream>
#include "Parser.h"

using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		Parser parser("C:\\Users\\Aymane\\Documents\\Visual Studio 2012\\Projects\\ProjetBus\\Debug\\");
		ListePlaces * parking = parser.generateParking();
		parser.generateTrajet(*parking);
		vector<Vehicule> buses = parser.generateVehicules();
		vector<Mission> missions = parser.generateMissions();
		for(int i =0; i<buses.size(); i ++)
		{
			buses[i].ajouterMission(missions[i]);
			buses[i].afficherMissions();
		}
		parking->afficherListePlaces();
	}
	catch(exception * e)
	{
		cout << e->what() << endl;
	}
	system("pause");
	return 0;
}

