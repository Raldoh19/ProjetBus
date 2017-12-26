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

void Vehicule::afficherMissions(){
	int i;
	std::cout<<"Missions pour le bus " << ID << " : " <<std::endl;
	for(i = 0; i < nbMissions; i++){
		std::cout<<"	Mission " << missions[i].getID() << " : dateArr " << missions[i].getDateArrivee().toString() << " dateDep " << missions[i].getDateDepart().toString() << std::endl;
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