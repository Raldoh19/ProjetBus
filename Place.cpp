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
	std::cout << "Place numero [taille:" << this->taillePlace << "] : " << this->numeroPlace;
	if(this->numeroVehicule == -1)
		std::cout << " - LIBRE" << std::endl;
	else
		std::cout << " - Vehicule stationne: " << this->numeroVehicule << std::endl;

	std:: cout << " Chemin d'acces [" << this->placeAcces->getNbPlaces() << "] : ";
	this->placeAcces->afficherSuite();
	std:: cout << " Chemin de sortie: [" << this->placeSortie->getNbPlaces() << "] : ";
	this->placeSortie->afficherSuite();
}

void Place::setPlaceAcces(ListePlaces * pa)
{
	this->placeAcces = pa;
}
void Place::setPlaceSortie(ListePlaces * ps)
{
	this->placeSortie = ps;
}

bool Place::peutAcceder(int taille)
{
	if(placeAcces == NULL)
	{
		return true;
	}
	for(int i =0 ; i < this->placeAcces->getNbPlaces(); i++)
	{
		Place * currentPlace = this->placeAcces->getPlaceIndex(i);
		if(currentPlace->getNumeroVehicule() != -1)
			return false;
	}
	if(this->getTaillePlace() != taille)
		return false;

	return true;
}

bool Place::peutSortir()
{
	if(placeSortie == NULL)
	{
		return true;
	}
	for(int i =0 ; i < this->placeSortie->getNbPlaces(); i++)
	{
		Place * currentPlace = this->placeSortie->getPlaceIndex(i);
		if(currentPlace->getNumeroVehicule() != -1)
			return false;
	}
	return true;
}

bool Place::operator<(const Place& st)
{
	return this->placeSortie->getNbPlaces() < st.placeSortie->getNbPlaces();
}