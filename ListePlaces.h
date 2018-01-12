#ifndef LISTESPLACES_H
#define LISTESPLACES_H

#include <vector>
#include <iostream>
#include <string>

class Place;

class ListePlaces
{
private:
	std::vector<Place*> listePlaces;
public:
	ListePlaces(void);
	int getNbPlaces();
	Place * getPlace(std::string numero);
	void ajouterPlace(Place *p);
	void supprimerPlace(Place *p);
	void afficherListePlaces();
	void afficherSuite();
	Place * recherchePlace(std::string placeCherche);
	Place * getPlaceVehicule(int numeroVehicule);
	Place * getPlaceIndex(int index);
	std::vector<Place*> getListePlaces();
	ListePlaces * subList(int indexDepart, int indexFin);
};

#endif