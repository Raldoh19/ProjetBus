// ProjetBus.cpp : définit le point d'entrée pour l'application console.
//

#include <iostream>
#include <algorithm>
#include "Parser.h"
#include "Solution.h"

using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		Date debut = Date(0,5,28,12,2017);
		Date fin = Date(0,1,29,12,2017);
		Parser parser("C:\\Users\\Aymane\\Documents\\Visual Studio 2012\\Projects\\ProjetBus\\Debug\\");
		vector<Vehicule*> buses = parser.generateVehicules();
		vector<Mission> missions = parser.generateMissions();
		ListePlaces * parking = parser.generateParking(missions, buses);
		parser.generateTrajet(*parking);
		for(int i = 0 ; i < buses.size(); i++)
		{
			buses[i]->afficherMissions();
		}
		//Solution(buses, *(parking)).nouveauParking(debut, fin);
	}
	catch(exception * e)
	{
		cout << e->what() << endl;
	}
	system("pause");
	return 0;
}

