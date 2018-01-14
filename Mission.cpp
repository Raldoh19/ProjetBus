#include "Mission.h"
#include <iostream>
#include <fstream>

using namespace std; 

/**
Constructeur pour Mission, il prendra en paramètre:
id : L'id de la mission
dateArr : La date de fin de la mission
dateDep : La date de départ de la mission
*/
Mission::Mission(int id, Date dateArr, Date dateDep)
{
	this->ID = id;
	if(dateArr.estApres(dateDep))
	{
		dateArrivee = dateArr;
		dateDepart = dateDep;
	}
	else
	{
		dateArrivee = dateDep;
		dateDepart = dateArr;
	}
}

/**
Getter pour l'ID de la mission
*/
int Mission::getID()
{
	return ID;
}

/**
Getter pour la dateArrivee de la mission
*/
Date Mission::getDateArrivee()
{
	return dateArrivee;
}

/**
Getter pour la dateDepart de la mission
*/
Date Mission::getDateDepart()
{
	return dateDepart;
}

/**
	operateur < pour différencier entre Mission
	*/
bool Mission::operator<(const Mission& mission)
{
	return this->dateDepart.estAvant(mission.dateDepart);
}

/**
Methode pour afficher la mission
*/
void Mission::afficher()
{
	std::cout << 
		"\t\t[" << ID << "]" << std::endl << 
		"\tDate debut: " << dateDepart.toString() << std::endl <<
		"\tDate arrivee : " << dateArrivee.toString() << std::endl;
}
/**
Methode pour decaler la mission d'un jour
*/
void Mission::plusOneDay()
{
	dateDepart.ajouterJour(1);
	dateArrivee.ajouterJour(1);
}
