#pragma once
#include "Date.h"
class Caracteristique
{
private:
	int idVehicule;
	int numeroPlace;
	Date dateArrive;
public:
	Caracteristique(void);
	Caracteristique(int, int, Date);
	~Caracteristique(void);
};

