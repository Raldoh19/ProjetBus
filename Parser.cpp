#include "Parser.h"
#include "Place.h"
#include <fstream>
#include <iostream>

using namespace std;

int split(vector<string>& vecteur, string chaineASplit, char separateur)
{
	vecteur.clear();
	string::size_type stTemp = chaineASplit.find(separateur);
	while(stTemp != string::npos)
	{
		vecteur.push_back(chaineASplit.substr(0, stTemp));
		chaineASplit = chaineASplit.substr(stTemp + 1);
		stTemp = chaineASplit.find(separateur);
	}
	vecteur.push_back(chaineASplit);
	return vecteur.size();
}

Date createDate(string chaine)
{
	vector<string> heureMinute;
	int checkSyntaxeHeure = split(heureMinute, chaine,':');
	if(checkSyntaxeHeure == 2)
	{
		try
		{
			return Date(stoi(heureMinute[1]), stoi(heureMinute[0]), 14,12,2017);
		}
		catch(invalid_argument ia)
		{
		}
	}
}

Parser::Parser(void)
{
	this->file = "";
}

Parser::Parser(string file)
{
	this->file= file;
}

void Parser::setFile(string file)
{
	this->file= file;
}

ListePlaces* Parser::generateParking()
{
	ListePlaces * parking = new ListePlaces();
	ifstream fichier(this->file);
	string ligne;
	if(fichier.is_open())
	{
		while(getline(fichier, ligne))
		{
			vector<string> ligneDecoupe;
			int nombreElement = split(ligneDecoupe, ligne, ';');
			if(nombreElement == 3)
			{
				if(ligneDecoupe[2].length() == 0)
					try
					{
						parking->ajouterPlace(Place(ligneDecoupe[0], stoi(ligneDecoupe[1])));
					}
					catch(invalid_argument ia)
					{
					}
				else
					try
					{
					parking->ajouterPlace(Place(ligneDecoupe[0], stoi(ligneDecoupe[1]), stoi(ligneDecoupe[2])));
					}
					catch(invalid_argument ia)
					{
					}
			}
			else
				throw new exception("Fichier CSV mal configure");
		}
		fichier.close();
		return parking;
	}
	else throw new exception("Impossible d'ouvrir le fichier!");
}

vector<Vehicule> Parser::generateVehicules()
{
	vector<Vehicule> vehiculeGeneres;
	ifstream fichier(this->file);
	string ligne;
	if(fichier.is_open())
	{
		while(getline(fichier, ligne))
		{
			vector<string> ligneDecoupe;
			int nombreElement = split(ligneDecoupe, ligne,';');
			if(nombreElement == 5)
			{
				try
				{
				vehiculeGeneres.push_back(Vehicule(stoi(ligneDecoupe[0]), stoi(ligneDecoupe[2])));
				}
				catch(invalid_argument ia)
				{
				}
			}
			else
				throw new exception("[Generation de vehicule] Fichier CSV mal configure");
		}
		fichier.close();
		return vehiculeGeneres;
	}
	else throw new exception("Impossible d'ouvrir le fichier!");
}

vector<Mission> Parser::generateMissions()
{
	vector<Mission> missionsGeneres;
	ifstream fichier(this->file);
	string ligne;
	if(fichier.is_open())
	{
		while(getline(fichier, ligne))
		{
			vector<string> ligneDecoupe;
			int nombreElement = split(ligneDecoupe, ligne,';');
			if(nombreElement == 9)
			{
				missionsGeneres.push_back(Mission(stoi(ligneDecoupe[0]), createDate(ligneDecoupe[2]), createDate(ligneDecoupe[1])));
			}
			else
				throw new exception("Fichier CSV mal configure");
		}
		fichier.close();
		return missionsGeneres;
	}
	else throw new exception("Impossible d'ouvrir le fichier!");
}

Parser::~Parser(void)
{
}
