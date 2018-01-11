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
	Mission();
	Mission(int id, Date dateArr, Date dateDep);
	~Mission();
	int getID();
	Date getDateArrivee();
	Date getDateDepart();
	bool operator<(const Mission& st);
	void afficher();
};

#endif