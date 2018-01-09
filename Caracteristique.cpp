#include "Caracteristique.h"


Caracteristique::Caracteristique(void)
{
}

Caracteristique::Caracteristique(int idVeh, std::string idPl, Date date)
{
	this->idVehicule = idVeh;
	this->numeroPlace = idPl;
	this->dateArrive = date;
}

Caracteristique::~Caracteristique(void)
{
}

