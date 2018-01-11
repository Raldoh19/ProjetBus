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
	Date(Date copie, int h, int mn);
	bool estAvant(Date d);
	bool estApres(Date d);
	bool estEgale(Date d);

	//void ajouterMinute(int);
	void ajouterHeure(int);
	void ajouterJour(int);
	void ajouterMois(int);
	void ajouterAnnee(int);
	void setTime(int h, int mn);
	std::string getHour();
	std::string toString();
	void ajouterMinutes(int nbMinutes);
	~Date(void);
};

#endif