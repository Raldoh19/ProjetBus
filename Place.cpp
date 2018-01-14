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
}

Place::Place(string num,int taille)
{
	numeroPlace = num;
	taillePlace = taille;
	this->numeroVehicule = -1;
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

std::vector<ListePlaces*> Place::getPlaceAcces(){
	return placeAcces;
}

std::vector<ListePlaces*> Place::getPlaceSortie(){
	return placeSortie;
}

void Place::afficher()
{
	std::cout << "Place numero [taille:" << this->taillePlace << "] : " << this->numeroPlace;
	if(this->numeroVehicule == -1)
		std::cout << " - LIBRE" << std::endl;
	else
		std::cout << " - Vehicule stationne: " << this->numeroVehicule << std::endl;

	std:: cout << " Chemin d'acces: " << std::endl;
	for(int i = 0 ; i < this->placeAcces.size(); i++)
	{
		std::cout << "\t" << i+1 << " chemin possible : ";
		this->placeAcces[i]->afficherSuite();
	}

	std:: cout << " Chemin de sortie: " << std::endl;
	for(int i = 0 ; i < this->placeSortie.size(); i++)
	{
		std::cout << "\t" << i+1 << " chemin possible : ";
		this->placeSortie[i]->afficherSuite();
	}	
}

void Place::setPlaceAcces(ListePlaces * pa)
{
	this->placeAcces.push_back(pa);
}
void Place::setPlaceSortie(ListePlaces * ps)
{
	this->placeSortie.push_back(ps);
}

bool Place::peutAcceder(int taille)
{
	if(placeAcces.size() == 0)
	{
		return true;
	}
	for(int t = 0; t < placeAcces.size() ; t++)
	{
		for(int i =0 ; i < this->placeAcces[t]->getNbPlaces(); i++)
		{
			Place * currentPlace = this->placeAcces[t]->getPlaceIndex(i);
			if(currentPlace->getNumeroVehicule() != -1)
				return false;
		}
	}
	if(this->getTaillePlace() != taille)
		return false;

	return true;
}

bool Place::peutSortir()
{
	if(placeSortie.size() == NULL)
	{
		return true;
	}

	for(int t = 0; t < placeSortie.size() ; t++)
	{
		for(int i =0 ; i < this->placeSortie[t]->getNbPlaces(); i++)
		{
			Place * currentPlace = this->placeSortie[t]->getPlaceIndex(i);
			if(currentPlace->getNumeroVehicule() != -1)
				return false;
		}
	}

	return true;
}

bool Place::operator<(Place& st)
{
	int minPlaceThis = 9999;
	for(int t = 0 ; t < placeSortie.size() ; t++)
		if(this->placeSortie[t]->getNbPlaces() <= minPlaceThis)
			minPlaceThis = this->placeSortie[t]->getNbPlaces();

	int minPlaceAutre = 9999;
	for(int t = 0 ; t < st.getPlaceSortie().size() ; t++)
		if(st.getPlaceSortie()[t]->getNbPlaces() <= minPlaceAutre)
			minPlaceAutre = st.getPlaceSortie()[t]->getNbPlaces();

	return minPlaceThis < minPlaceAutre;
}