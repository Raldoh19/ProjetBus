#include "ListePlaces.h"
#include <iostream>
#include "Place.h"
#include <algorithm>
/**
Constrcuteur par d�faut
*/
ListePlaces::ListePlaces()
{

}

/**
Getter pour le nombre de place pr�sent
*/
int ListePlaces::getNbPlaces()
{
	return listePlaces.size();
}

/**
Methode pour ajouter une place
*/
void ListePlaces::ajouterPlace(Place *p)
{
	listePlaces.push_back(p);
}

/**
Methode pour supprimer une place
*/
void ListePlaces::supprimerPlace(Place *p)
{
    unsigned int i = 0;

    while( i < listePlaces.size() && (p->getNumeroPlace().compare(listePlaces[i]->getNumeroPlace()) == -1))
	{
        i++;
    }
    if( i == listePlaces.size())
	{
        std::cout<<"Place a retirer non trouve ! " << std::endl;
    }
	else
	{
        listePlaces.erase(listePlaces.begin() + i);
    }
}

/**
Methode pour afficher la liste des places
*/
void ListePlaces::afficherListePlaces()
{
	for(unsigned int i =0 ; i < listePlaces.size(); i++)
	{
		listePlaces[i]->afficher();
	}
}

/**
Methode qui retourne un objet Place avec le meme ID recherche
Le cr�e au cas ou ce dernier n'existe pas
*/
Place* ListePlaces::recherchePlace(std::string placeCherche)
{
	for(int i=0;i<this->listePlaces.size();i++)
	{
		if(listePlaces[i]->getNumeroPlace() == placeCherche)
			return listePlaces[i];
	}
	ajouterPlace(new Place(placeCherche,-1));
	return listePlaces[listePlaces.size()-1];
}

/**
Affiche les places sous forme d'une suite 
*/
void ListePlaces::afficherSuite()
{
	for(int i =0 ; i < listePlaces.size(); i++)
	{
		std::cout << this->listePlaces[i]->getNumeroPlace() << " - ";
	}
	std::cout << std::endl;
}

/**
Retourne l'objet Place situ� a l'index index
*/
Place * ListePlaces::getPlaceIndex(int index)
{
	if ((index >= this->listePlaces.size()) || (index < 0))
	{
		return NULL;
	}
	else
	{
		return listePlaces.at(index);
	}
}
/**
Retourne l'objet Place avec l'ID numero
*/
Place * ListePlaces::getPlace(std::string numero)
{
	unsigned int i = 0;
	while( i < listePlaces.size()){
		if(listePlaces.at(i)->getNumeroPlace().compare(numero) == 0){
			return listePlaces.at(i);
		}
		i++;
	}
	return NULL;
}

/**
Retourne l'objet Place avec le vehicule : numeroVehicule 
*/
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

/**
Retourne une partie de la liste 
*/
ListePlaces * ListePlaces::subList(int indexDepart, int indexFin)
{
	if(indexDepart >= 0 && indexFin <= listePlaces.size())
	{
		ListePlaces * toReturn = new ListePlaces();
		for(int i = indexDepart; i < indexFin; i++)
		{
			toReturn->ajouterPlace(this->listePlaces[i]);
		}
		return toReturn;
	}
	else
		return NULL;
	
}

/**
Retourne la liste de place enti�res
*/
std::vector<Place*> ListePlaces::getListePlaces(){
	return listePlaces;
}

/**
Methode qui trie les places selon les plus proche de la sortie
*/
void ListePlaces::triListe()
{
	std::sort(listePlaces.begin(), listePlaces.end(), [ ]( Place* first, Place* second )
	{
		int minPlaceFirst = 9999;
		for(int t = 0 ; t < first->getPlaceSortie().size() ; t++)
			if(first->getPlaceSortie()[t]->getNbPlaces() <= minPlaceFirst)
				minPlaceFirst = first->getPlaceSortie()[t]->getNbPlaces();

		int minPlaceSecond = 9999;
		for(int t = 0 ; t < second->getPlaceSortie().size() ; t++)
			if(second->getPlaceSortie()[t]->getNbPlaces() <= minPlaceSecond)
				minPlaceSecond = second->getPlaceSortie()[t]->getNbPlaces();

		return minPlaceFirst < minPlaceSecond;
	});
}

/**
Methode qui trie les places selon les plus proche de la sortie
*/

ListePlaces * ListePlaces::getPlaceVide(int taille)
{
	ListePlaces * toReturn = new ListePlaces();
	for(int i = 0; i < this->listePlaces.size() ; i++)
	{
		if(listePlaces[i]->getNumeroVehicule() == -1 && listePlaces[i]->getTaillePlace() == taille)
			toReturn->ajouterPlace(this->listePlaces[i]);
	}
	return toReturn;
}