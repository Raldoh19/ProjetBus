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
	Caracteristique(int, std::string, Date);
	int getIdVehicule();
	std::string getNumeroPlace();
	Date getDateArrivee();
	void toString();
};
#endif
