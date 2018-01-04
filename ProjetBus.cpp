// ProjetBus.cpp : définit le point d'entrée pour l'application console.
//

#include <iostream>
#include "Parser.h"
#include "ListePlaces.h"
#include "Place.h"
#include "Solution.h"
using namespace std;

int main(int argc, char* argv[])
{
	
	/*try
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
	}*/


	Place place1 = Place("01",1);
	ListePlaces parking = ListePlaces();
	parking.ajouterPlace(place1);

	Mission m1 = Mission(0,Date(10,10,10,10,2010),Date(10,11,10,10,2010));
	Vehicule bus1 = Vehicule(0,1);
	bus1.ajouterMission(m1);

	parking.afficherListePlaces();
	bus1.afficherMissions();

	Solution solver = Solution();
	vector<string> placesVides = solver.getPlacesVides(parking);

	cout<<"places vides : "<< placesVides.at(0) << endl;
		
	system("pause");
	return 0;
}

