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
	unsigned int nbPlaces;
public:
	ListePlaces(void);
	~ListePlaces(void);
	ListePlaces(int nb);
	Place * getPlace(std::string numero);
	int getNbPlaces();
	void ajouterPlace(Place *p);
	void supprimerPlace(Place *p);
	void afficherListePlaces();

	void afficher();
	void afficherSuite();
	Place * recherchePlace(std::string placeCherche);

	std::vector<Place*> getListePlaces();


};

#endif