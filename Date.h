#ifndef DATE_H
#define DATE_H

#include <string>
class Date
{
private:
	int minutes;
	int heure;
	int jour;
	int mois;
	int annee;
public:
	Date();
	Date(int mn,int h,int j, int m, int a);
	bool estAvant(Date d);
	bool estApres(Date d);
	bool estEgale(Date d);
	std::string toString();
	~Date(void);
};

#endif