#include "Date.h"
#include <iostream>

/** 
Constructeur pour la date sous le format suivant:  MM:HH JJ/MM/AAA
*/
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

/**
Constructeur de recopie d'une date avec un changement au niveau de l'horaire
*/
Date::Date(Date copie, int h, int mn)
{
	this->minutes = mn;
	this->heure = h;
	this->jour = copie.jour;
	this->mois = copie.mois;
	this->annee = copie.annee;
}

// TEST COMPARAISON

/**
	Test pour voir si notre Date est avant la date d 
*/
bool Date::estAvant(Date d)
{
	return( (d.annee > this->annee) || 
		(d.annee == this->annee && d.mois > this->mois) || 
		(d.annee == this->annee && d.mois == this->mois && d.jour > this->jour) || 
		(d.annee == this->annee && d.mois == this->mois && d.jour == this->jour && d.heure > this->heure) ||
		(d.annee == this->annee && d.mois == this->mois && d.jour == this->jour && d.heure == this->heure && d.minutes > this->minutes));
}

/**
	Test pour voir si notre Date est apres la date d 
*/
bool Date::estApres(Date d)
{
	return( (d.annee < this->annee) || 
		(d.annee == this->annee && d.mois < this->mois) || 
		(d.annee == this->annee && d.mois == this->mois && d.jour < this->jour) || 
		(d.annee == this->annee && d.mois == this->mois && d.jour == this->jour && d.heure < this->heure) ||
		(d.annee == this->annee && d.mois == this->mois && d.jour == this->jour && d.heure == this->heure && d.minutes < this->minutes));
}

/**
	Test pour voir si notre Date est egale la date d 
*/
bool Date::estEgale(Date d)
{
	return (d.annee == this->annee && d.mois == this->mois && d.jour == this->jour && d.heure == this->heure && d.minutes == this->minutes);
}
	

// GETTER
/**
	Getter pour obtenir l'heure de la date sous le format HH:MM
*/
std::string Date::getHour()
{
	return std::to_string(heure).append(":").append(std::to_string(minutes));
}

/**
	Getter pour obtenir l'heure de la date JJ MM AAA HH:MM
*/
std::string Date::toString(){
	return std::to_string(jour).append(" ").append(std::to_string(mois)).append(" ").append(std::to_string(annee)).append(" ").append(std::to_string(heure)).append(" ").append(std::to_string(minutes));
}

/**
	Getter pour obtenir les minutes
*/
int Date::getMinutes()
{
	return this->minutes;
}

/**
	Getter pour obtenir les heures
*/
int Date::getHeures()
{
	return this->heure;
}


// SETTERS 
/**
	Ajout de nbMinutes a notre date
*/
void Date::ajouterMinutes(int nbMinutes)
{
	if( minutes + nbMinutes >=60)
	{
		++heure;
		minutes = nbMinutes + minutes - 60;
	}
	else
	{
		minutes += nbMinutes;
	}
}

/**
	Ajout de nbHeures a notre date
*/
void Date::ajouterHeure(int nbHeures)
{
	if( heure + nbHeures >= 24)
	{
		++jour;
		heure = nbHeures + heure - 24;
	}
	else
	{
		heure += nbHeures;
	}
}

/**
	Ajout de jour a notre date
*/
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

/**
	Ajout de mois a notre date
*/
void Date::ajouterMois(int mois)
{
	this->mois = this->mois + mois;
	if(this->mois > 12)
	{
		this->ajouterAnnee(this->mois/12);
		this->mois = this->mois % 12;
	}
}

/**
	Ajout de annee a notre date
*/
void Date::ajouterAnnee(int annee)
{
	this->annee = this->annee + annee;
}

/**
	On modifie l'horaire de notre date a : h:m
*/
void Date::setTime(int h, int mn)
{
	this->heure = h;
	this->minutes = mn;
}