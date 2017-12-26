#include "ListePlaces.h"
#include <iostream>
#include "Place.h"

ListePlaces::ListePlaces(void)
{
	nbPlaces = 0;
}

ListePlaces::~ListePlaces(void)
{

}

ListePlaces::ListePlaces(int nb)
{
	listePlaces.reserve(nb);
	nbPlaces = nb;
}

int ListePlaces::getNbPlaces()
{
	return nbPlaces;
}

void ListePlaces::ajouterPlace(Place p)
{
	listePlaces.push_back(p);
	nbPlaces++;
}

void ListePlaces::supprimerPlace(Place p)
{
    unsigned int i = 0;

    while( i < nbPlaces && (p.getNumeroPlace().compare(listePlaces[i].getNumeroPlace()) == -1))
	{
        i++;
    }
    if( i == nbPlaces)
	{
        std::cout<<"Place a retirer non trouve ! " << std::endl;
        //throw exc ? 
    }
	else
	{
        listePlaces.erase(listePlaces.begin() + i);
        nbPlaces--;
    }
}

void ListePlaces::afficherListePlaces()
{
	for(unsigned int i =0 ; i < nbPlaces; i++)
	{
		listePlaces[i].afficher();
	}
}
