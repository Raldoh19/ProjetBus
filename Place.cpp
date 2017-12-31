#include "Place.h"
#include "ListePlaces.h"

Place::Place()
{

}

Place::Place(string num,int taille, int numeroVehicule)
{
	numeroPlace = num;
	taillePlace = taille;
	this->numeroVehicule = numeroVehicule;
	placeAcces = new ListePlaces();
	placeSortie = new ListePlaces();
}

Place::Place(string num,int taille)
{
	numeroPlace = num;
	taillePlace = taille;
	this->numeroVehicule = -1;
	placeAcces = new ListePlaces();
	placeSortie = new ListePlaces();
}

Place::~Place(void)
{

}

string Place::getNumeroPlace(){
	return numeroPlace;
}

int Place::getTaillePlace(){
	return taillePlace;
}

int Place::getNumeroVehicule(){
	return this->numeroVehicule;
}

void Place::setNumeroPlace(string num){
	numeroPlace = num;
}

void Place::setTaillePlace(int taille){
	taillePlace = taille;
}

void Place::setNumeroVehicule(int numeroVehicule){
	this->numeroVehicule = numeroVehicule;
}

ListePlaces* Place::getPlaceAcces(){
	return placeAcces;
}

ListePlaces* Place::getPlaceSortie(){
	return placeSortie;
}

void Place::afficher()
{
	std::cout << "Place numero: " << this->numeroPlace;
	if(this->numeroVehicule == -1)
		std::cout << " - LIBRE" << std::endl;
	else
		std::cout << " - Vehicule stationné: " << this->numeroVehicule << std::endl;
}