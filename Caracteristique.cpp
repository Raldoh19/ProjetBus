#include "Caracteristique.h"

/**
Constructeur pour les caracteristiques, il prendra en parametre:
	l'id d'un vehicule
	l'id de sa place
	la date a laquelle il a stationné
*/
Caracteristique::Caracteristique(int idVeh, std::string idPl, Date date)
{
	this->idVehicule = idVeh;
	this->numeroPlace = idPl;
	this->dateArrive = date;
}

/**
	Getter pour l'id du vehicule
*/
int Caracteristique::getIdVehicule(){
	return idVehicule;
}

/**
	Getter pour l'id de la place
*/
std::string Caracteristique::getNumeroPlace(){
	return numeroPlace;
}

/**
	Getter pour la date d'arrivee
*/
Date Caracteristique::getDateArrivee(){
	return dateArrive;
}

/**
	Affichage de la caracteristique
*/
void Caracteristique::toString()
{
	std::cout << "Le vehicule " << idVehicule << " est stationné en " << numeroPlace << std::endl;
	std::cout << "Heure arrive: " << dateArrive.toString() << std::endl;
}
