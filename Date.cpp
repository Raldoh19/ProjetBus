#include "Date.h"

Date::Date()
{
}

Date::Date(int mn,int h,int j, int m, int a)
{
	minutes = mn;
	heure = h;
	jour = j;
	mois = m;
	annee = a;
}

bool Date::estAvant(Date d)
{
	return( (d.annee > this->annee) || 
		(d.annee == this->annee && d.mois > this->mois) || 
		(d.annee == this->annee && d.mois == this->mois && d.jour > this->jour) || 
		(d.annee == this->annee && d.mois == this->mois && d.jour == this->jour && d.heure > this->heure) ||
		(d.annee == this->annee && d.mois == this->mois && d.jour == this->jour && d.heure == this->heure && d.minutes > this->minutes));
}

bool Date::estApres(Date d)
{
	return( (d.annee < this->annee) || 
		(d.annee == this->annee && d.mois < this->mois) || 
		(d.annee == this->annee && d.mois == this->mois && d.jour < this->jour) || 
		(d.annee == this->annee && d.mois == this->mois && d.jour == this->jour && d.heure < this->heure) ||
		(d.annee == this->annee && d.mois == this->mois && d.jour == this->jour && d.heure == this->heure && d.minutes < this->minutes));
}

bool Date::estEgale(Date d)
{
	return (d.annee == this->annee && d.mois == this->mois && d.jour == this->jour && d.heure == this->heure && d.minutes == this->minutes);
}
	
void Date::ajouterMinutes(int nbMinutes){
	if( minutes + nbMinutes >=60){
		++heure;
		minutes = nbMinutes + minutes - 60;
	}else{
		minutes += nbMinutes;
	}
}
Date::~Date(void)
{

}

std::string Date::toString(){
	return std::to_string(jour).append(" ").append(std::to_string(mois)).append(" ").append(std::to_string(annee)).append(" ").append(std::to_string(heure)).append(" ").append(std::to_string(minutes));
}

