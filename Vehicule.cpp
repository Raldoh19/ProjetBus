#include "Vehicule.h"
#include <stdlib.h>
#include <iostream>

Vehicule::Vehicule(int id, int taille){
	ID = id;
	tailleVehicule = taille;
	nbMissions = 0;
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

void Vehicule::ajouterMission(Mission m){
	missions.push_back(m);
	nbMissions++;

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

    while( i < nbMissions && m.getID() != missions[i].getID())
	{
        i++;
    }
    if( i == nbMissions)
	{
        std::cout<<"Mission a retirer non trouve ! " << std::endl;
        //throw exc ? 
    }
	else
	{
        missions.erase(missions.begin() + i);
        nbMissions--;
    }
}

std::vector<Mission> Vehicule::getMissions(){
	return missions;
}

int Vehicule::getNbMissions(){
	return nbMissions;
}