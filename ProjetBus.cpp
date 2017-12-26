// ProjetBus.cpp : définit le point d'entrée pour l'application console.
//

#include <iostream>
#include "Parser.h"

using namespace std;

int main(int argc, char* argv[])
{
	
	try
	{
		ListePlaces * parking = Parser("F:\\ProjetVisualStudio\\ProjetBus\\DonneesBus\\entrees_bus_petit_volume\\Emplacement.csv").generateParking();
		vector<Vehicule> buses = Parser("F:\\ProjetVisualStudio\\ProjetBus\\DonneesBus\\entrees_bus_petit_volume\\Vehicule.csv").generateVehicules();
		vector<Mission> missions = Parser("F:\\ProjetVisualStudio\\ProjetBus\\DonneesBus\\entrees_bus_petit_volume\\Mission.csv").generateMissions();
		for(unsigned int i =0; i<buses.size(); i ++)
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

