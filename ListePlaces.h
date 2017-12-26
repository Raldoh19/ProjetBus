#ifndef LISTESPLACES_H
#define LISTESPLACES_H

#include <vector>
#include <iostream>

class Place;

class ListePlaces
{
private:
	std::vector<Place> listePlaces;
	unsigned int nbPlaces;
public:
	ListePlaces(void);
	~ListePlaces(void);
	ListePlaces(int nb);
	int getNbPlaces();
	void ajouterPlace(Place p);
	void supprimerPlace(Place p);
	void afficherListePlaces();
	Place & recherchePlace(string);

};

#endif