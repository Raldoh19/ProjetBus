#include "Mission.h"
#include <iostream>

Mission::Mission()
{

}

Mission::Mission(int id, Date dateArr, Date dateDep)
{
	this->ID = id;
	dateArrivee = dateArr;
	dateDepart = dateDep;
}

Mission::~Mission()
{
}

int Mission::getID()
{
	return ID;
}

Date Mission::getDateArrivee()
{
	return dateArrivee;
}
	
Date Mission::getDateDepart()
{
	return dateDepart;
}

bool Mission::operator<(const Mission& mission)
{
	return this->dateDepart.estAvant(mission.dateDepart);
}

void Mission::afficher()
{
	std::cout << 
		"\t\t[" << ID << "]" << std::endl << 
		"\tDate debut: " << dateDepart.toString() << std::endl <<
		"\tDate arrivee : " << dateArrivee.toString() << std::endl;
}