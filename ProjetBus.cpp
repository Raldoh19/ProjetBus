// ProjetBus.cpp : définit le point d'entrée pour l'application console.
//

#include <iostream>
#include <algorithm>
#include "Parser.h"
#include "ListePlaces.h"
#include "Place.h"
#include "Solution.h"
#include "Generateur.h"

using namespace std;


int main(int argc, char* argv[])
{
	
	try
	{

		Date debut = Date(0,5,14,12,2017);
		Date fin = Date(59,23,15,12,2017);

		Parser parser("C:\\Users\\Aymane\\Documents\\Visual Studio 2012\\Projects\\ProjetBus\\Debug\\");
		Generateur generator("C:\\Users\\Aymane\\Documents\\Visual Studio 2012\\Projects\\ProjetBus\\Debug\\");
		//Parser parser("F:\\ProjetVisualStudio\\ProjetBus\\ProjetBus\\Debug\\DonneesBus\\entrees_volume\\");
		//Generateur generator("F:\\ProjetVisualStudio\\ProjetBus\\ProjetBus\\Debug\\DonneesBus\\entrees_volume\\");
		generator.generateParkingA(110,22);
		system("pause");
		vector<Vehicule*> buses = parser.generateVehicules();
		generator.generateMissions(buses.size(), debut, fin);

		vector<Mission> missions = parser.generateMissions();
		ListePlaces * parking = parser.generateParking(missions, buses);
		ListePlaces * parkingCopie = parser.generateParking(missions, buses);
		parser.generateTrajet(*parking);
		parser.generateTrajet(*parkingCopie);
		
		vector<Vehicule> busConcerne;
		for(unsigned int i =0; i<buses.size(); i ++)
		{
			busConcerne.push_back(*(buses[i]));
		}
		Solution s1(*(parking), busConcerne);
		s1.nouveauParking(debut, fin);
		
		s1.verificationSolution(s1,*parkingCopie,debut,fin);
	}
	catch(exception * e)
	{
		cout << e->what() << endl;
	}
	system("pause");
	return 0;
}

