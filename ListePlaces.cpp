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

std::vector<Place*> ListePlaces::getListePlaces(){
	return listePlaces;
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

void ListePlaces::ajouterPlace(Place *p)
{
	listePlaces.push_back(p);
	nbPlaces++;
}

void ListePlaces::supprimerPlace(Place *p)
{
    unsigned int i = 0;

    while( i < nbPlaces && (p->getNumeroPlace().compare(listePlaces[i]->getNumeroPlace()) == -1))
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
		listePlaces[i]->afficher();
	}
}


Place* ListePlaces::recherchePlace(std::string placeCherche)
{
	for(int i=0;i<this->nbPlaces;i++)
	{
		if(listePlaces[i]->getNumeroPlace() == placeCherche)
			return listePlaces[i];
	}
	ajouterPlace(new Place(placeCherche,-1));
	return listePlaces[listePlaces.size()-1];
}


void ListePlaces::afficher()
{
	for(int i =0 ; i < nbPlaces; i++)
	{
		listePlaces[i]->afficher();
	}
	std::cout << std::endl;
}

void ListePlaces::afficherSuite()
{
	for(int i =0 ; i < nbPlaces; i++)
	{
		std::cout << this->listePlaces[i]->getNumeroPlace() << " - ";
	}
	std::cout << std::endl;
}


Place * ListePlaces::getPlaceIndex(int index)
{
	if ((index >= this->nbPlaces) || (index < 0))
	{
		throw exception("Place introuvable !");
	}
	else
	{
		return listePlaces.at(index);
	}
}
Place * ListePlaces::getPlace(std::string numero)
{
	unsigned int i = 0;
	while( i < listePlaces.size()){
		if(listePlaces.at(i)->getNumeroPlace().compare(numero) == 0){
			return listePlaces.at(i);
		}
		i++;
	}
	throw exception("Place introuvable !");
}

Place * ListePlaces::getPlaceVehicule(int numeroVehicule)
{
	unsigned int i = 0;
	for(int i = 0; i< this->listePlaces.size() ; i++) 
	{
		if(listePlaces[i]->getNumeroVehicule() == numeroVehicule)
		{
			return listePlaces[i];
		}
	}
	return NULL;
}
