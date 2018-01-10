#ifndef CARACTERISTIQUE_H
#define CARACTERITSIQUE

#include "Date.h"
#include <iostream>
#include <vector>
class Caracteristique
{
private:
	int idVehicule;
	std::string numeroPlace;
	Date dateArrive;
public:
	Caracteristique(void);
	Caracteristique(int, std::string, Date);
	~Caracteristique(void);

	int getIdVehicule(){
		return idVehicule;
	}

	std::string getNumeroPlace(){
		return numeroPlace;
	}

	Date getDateArrivee(){
		return dateArrive;
	}

	void toString()
	{
		std::cout << "Le vehicule " << idVehicule << " est stationné en " << numeroPlace << std::endl;
		std::cout << "Heure arrive: " << dateArrive.toString() << std::endl;

	}
};
#endif
