#include "Vehicule.h"
#include <stdlib.h>
#include <iostream>
#include <algorithm>



Vehicule::Vehicule(int id, int taille){
	ID = id;
	tailleVehicule = taille;
}

Vehicule::~Vehicule(){
		
}

int Vehicule::getID(){
	return ID;
}

int Vehicule::getTailleVehicule(){
	return tailleVehicule;
}

void Vehicule::setID(int id){
	ID = id;
}

void Vehicule::setTailleVehicule(int taille){
	tailleVehicule = taille;
}

void Vehicule::ajouterMission(Mission m)
{
	missions.push_back(m);
	std::sort(missions.begin(), missions.end());
}

void Vehicule::afficherMissions()
{
	std::cout << "Mission du bus " << ID << " : " << std::endl;
	for(int i = 0; i <  missions.size() ; i++)
	{
		missions[i].afficher();
	}
}

void Vehicule::retirerMission(Mission m)
{
    int i = 0;

    while( i < missions.size() && m.getID() != missions[i].getID())
	{
        i++;
    }
    if( i ==  missions.size())
	{
        std::cout<<"Mission a retirer non trouve ! " << std::endl;
    }
	else
	{
        missions.erase(missions.begin() + i);
		std::sort(missions.begin(), missions.end());
    }
}

std::vector<Mission> Vehicule::getMissions(){
	return missions;
}

int Vehicule::getNbMissions(){
	return  missions.size();
}
