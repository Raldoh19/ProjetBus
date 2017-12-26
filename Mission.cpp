#include "Mission.h"


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