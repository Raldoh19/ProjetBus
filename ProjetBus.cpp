// ProjetBus.cpp : définit le point d'entrée pour l'application console.
//

#include <iostream>
#include <algorithm>
#include "Parser.h"
#include "ListePlaces.h"
#include "Place.h"
#include "Solution.h"

using namespace std;


int main(int argc, char* argv[])
{
	
	try
	{

		Date debut = Date(0,5,14,12,2017);
		Date fin = Date(59,23,14,12,2017);
		//Parser parser("C:\\Users\\Aymane\\Documents\\Visual Studio 2012\\Projects\\ProjetBus\\Debug\\");
		Parser parser("F:\\ProjetVisualStudio\\ProjetBus\\ProjetBus\\Debug\\DonneesBus\\entrees_volume\\");
		vector<Vehicule*> buses = parser.generateVehicules();
		vector<Mission> missions = parser.generateMissions();
		ListePlaces * parking = parser.generateParking(missions, buses);
		parser.generateTrajet(*parking);
		vector<Vehicule> busConcerne;
		for(unsigned int i =0; i<buses.size(); i ++)
		{
			busConcerne.push_back(*(buses[i]));
		}
		system("pause");
		Solution s1(*(parking), busConcerne);
		s1.nouveauParking(debut, fin);
		s1.verificationSolution(s1,*parking);
		system("pause");
	}
	catch(exception * e)
	{
		cout << e->what() << endl;
	}

	system("pause");
	return 0;
}

