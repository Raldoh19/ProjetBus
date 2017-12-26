#include "Caracteristique.h"


Caracteristique::Caracteristique(void)
{
}

Caracteristique::Caracteristique(int idVeh, int idPl, Date date)
{
	this->idVehicule = idVeh;
	this->numeroPlace = idPl;
	this->dateArrive = date;
}

Caracteristique::~Caracteristique(void)
{
}
