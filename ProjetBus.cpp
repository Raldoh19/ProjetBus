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
		Parser parser("C:\\Users\\Aymane\\Documents\\Visual Studio 2012\\Projects\\ProjetBus\\Debug\\");
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
		system("pause");
	}
	catch(exception * e)
	{
		cout << e->what() << endl;
	}

	/*
	Place place1 = Place("01",1);
	ListePlaces parking = ListePlaces();
	parking.ajouterPlace(&place1);

	Mission m1 = Mission(0,Date(10,9,10,10,2010),Date(10,10,10,10,2010));
	Vehicule bus1 = Vehicule(0,1);
	bus1.ajouterMission(m1);

	Mission m2 = Mission(0,Date(10,8,10,10,2010),Date(10,11,10,10,2010));
	Vehicule bus2 = Vehicule(1,1);
	bus2.ajouterMission(m2);

	std::vector<Vehicule> vehicules;
	vehicules.push_back(bus1);
	vehicules.push_back(bus2);

	//LE BUS1 EST GARE SUR LA PLACE 1
	place1.setNumeroVehicule(bus1.getID());
	parking.afficherListePlaces();*/
	

	return 0;
}

