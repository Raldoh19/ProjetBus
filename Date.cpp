#include "Date.h"
#include <iostream>

Date::Date()
{
}

Date::Date(int mn,int h,int j, int m, int a)
{
	if(mn > 60 || h > 23 || j > 31 || m > 12){
		std::cout<<"Erreur dans la date"<<std::endl;
		//throw 
	}
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

void Date::ajouterMinute(int minutes)
{
	this->minutes = this->minutes + minutes;
	if(this->minutes >= 60)
	{
		this->ajouterHeure(this->minutes/60);
		this->minutes = this->minutes % 60;
	}
}

void Date::ajouterHeure(int heure)
{
	this->heure = this->heure + heure;
	if(this->heure == 24)
	{
		this->ajouterJour(1);
		this->heure = 0;
	}
}

void Date::ajouterJour(int jour)
{
	this->jour = this->jour + jour;
	if((this->jour > 31) && (this->mois == 1 || this->mois == 3 || this->mois == 5 || this->mois == 7 || this->mois == 8 || this->mois == 10 || this->mois == 12))
	{
		this->ajouterMois(this->jour/31);
		this->jour = this->jour % 31;
	}
	else if( (this->jour > 29) && (this->mois == 2) && (this->annee % 4 == 0) )
	{
		this->ajouterMois(this->jour/29);
		this->jour = this->jour % 29;
	}
	else if( (this->jour > 28) && (this->mois == 2) && (this->annee % 4 != 0) )
	{
		this->ajouterMois(this->jour/28);
		this->jour = this->jour % 28;
	}
	else
	{
		this->ajouterMois(this->jour/30);
		this->jour = this->jour % 30;
	}
}

void Date::ajouterMois(int mois)
{
	this->mois = this->mois + mois;
	if(this->mois > 12)
	{
		this->ajouterAnnee(this->mois/12);
		this->mois = this->mois % 12;
	}
}

void Date::ajouterAnnee(int annee)
{
	this->annee = this->annee + annee;
}