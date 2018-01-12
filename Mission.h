#ifndef MISSION_H
#define MISSION_H
#include <vector>
#include "Date.h"
class Mission
{
private:
	int ID;
	Date dateArrivee;
	Date dateDepart;
public:
	Mission(int id, Date dateArr, Date dateDep);
	int getID();
	Date getDateArrivee();
	Date getDateDepart();
	bool operator<(const Mission& st);
	void afficher();
};

#endif