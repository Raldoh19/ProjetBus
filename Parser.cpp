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

ListePlaces* Parser::generateParking(vector<Mission> missions, vector<Vehicule*> buses)
{
	ListePlaces * parking = new ListePlaces();
	ifstream fichier(this->file+"Emplacement.csv");
	string ligne;
	if(fichier.is_open())
	{
		int indiceVehicule = 0;
		while(getline(fichier, ligne))
		{
			vector<string> ligneDecoupe;
			int nombreElement = split(ligneDecoupe, ligne, ';');
			if(nombreElement >= 3)
			{
				if(ligneDecoupe[2].length() == 0)
				{
					try
					{
						parking->ajouterPlace(new Place(ligneDecoupe[0], stoi(ligneDecoupe[1])));
					}
					catch(invalid_argument ia)
					{
					}
				}
				else
				{
					try
					{
						int numeroMission = stoi(ligneDecoupe[2]);
						bool missionChecked = false;
						int busID = 0;
						for(int i = 0; i < missions.size(); i++)
						{
							if(missions[i].getID() == numeroMission)
							{
								if(indiceVehicule >= buses.size())
								{
									bool madeIt = false;
									busID = 0;
									while(busID < buses.size() && madeIt == false)
									{
										Mission curMission = buses[busID]->getMissions()[buses[busID]->getMissions().size()-1];
										if(curMission.getDateArrivee().estAvant(missions[i].getDateDepart()))
										{
											buses[busID]->ajouterMission(missions[i]);
											parking->ajouterPlace(new Place(ligneDecoupe[0], stoi(ligneDecoupe[1]), buses[busID]->getID()));
											missionChecked=true;
											madeIt = true;
											break;
										}
										busID++;
									}
								}
								else
								{
									buses[indiceVehicule]->ajouterMission(missions[i]);
									parking->ajouterPlace(new Place(ligneDecoupe[0], stoi(ligneDecoupe[1]), buses[indiceVehicule]->getID()));
									missionChecked=true;
									busID = indiceVehicule;
									indiceVehicule++;
								}
							}
							if(missionChecked && i != 0)
							{
								if(missions[i].getDateDepart().estApres(missions[i-1].getDateDepart()))
								{
									buses[busID]->ajouterMission(missions[i]);
									missionChecked = false;
								}
							}
						}
					}
					catch(invalid_argument ia)
					{
					}
				}
			}
			else
				throw new exception("[Parking] Fichier CSV mal configure");
		}
		fichier.close();
		return parking;
	}
	else throw new exception("[Parking] Impossible d'ouvrir le fichier!");
}

vector<Vehicule*> Parser::generateVehicules()
{

	vector<Vehicule*> vehiculeGeneres;
	ifstream fichier(this->file+"Vehicule.csv");

	string ligne;
	if(fichier.is_open())
	{
		while(getline(fichier, ligne))
		{
			vector<string> ligneDecoupe;
			int nombreElement = split(ligneDecoupe, ligne,';');
			if(nombreElement >= 5)
			{
				try
				{
				vehiculeGeneres.push_back(new Vehicule(stoi(ligneDecoupe[0]), stoi(ligneDecoupe[2])));
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
	ifstream fichier(this->file+"Mission.csv");
	string ligne;
	if(fichier.is_open())
	{
		while(getline(fichier, ligne))
		{
			vector<string> ligneDecoupe;
			int nombreElement = split(ligneDecoupe, ligne,';');
			if(nombreElement >= 9)
			{
				Date dateDepart = createDate(ligneDecoupe[1]);
				Date dateArrivee = createDate(ligneDecoupe[2]);
				if(dateArrivee.estAvant(dateDepart))
					dateArrivee.ajouterJour(1);
				missionsGeneres.push_back(Mission(stoi(ligneDecoupe[0]), dateArrivee, dateDepart));
			}
			else
				throw new exception("[Mission] Fichier CSV mal configure");
		}
		fichier.close();
		return missionsGeneres;
	}
	else
	{
		throw new exception("[Mission] Impossible d'ouvrir le fichier!");
	}
}


void Parser::generateTrajet(ListePlaces parking)
{
	ifstream fichier(this->file+"Trajet.csv");
	string ligne;
	if(fichier.is_open())
	{
		while(getline(fichier, ligne))
		{
			vector<string> ligneDecoupe;
			int nombreElement = split(ligneDecoupe, ligne,';');
			if(nombreElement >= 3)
			{
				try
				{
					Place * placeConcerne = parking.recherchePlace(ligneDecoupe[0]);
					string ES = ligneDecoupe[2];
					ListePlaces * trajetPlace = new ListePlaces();
					vector<string> placeDecoupe;
					int nombrePlace = split(placeDecoupe, ligneDecoupe[1],',');
					for(int i = 0;i < nombrePlace;i++)
					{
						try
						{
						Place * placeGenere = parking.recherchePlace(placeDecoupe[i]);
						trajetPlace->ajouterPlace(placeGenere);
						}catch(exception * e)
						{
						}
					}
					if(ES == "S")
						placeConcerne->setPlaceSortie(trajetPlace);
					else
						placeConcerne->setPlaceAcces(trajetPlace);
				}
				catch(exception e)
				{
					std::cout << ligneDecoupe[0] << "ne figure pas dans le parking !" << std::endl;
				}
			}
			else
				throw new exception("[Trajet] Fichier CSV mal configure");
		}
		fichier.close();
	}
	else throw new exception("Impossible d'ouvrir le fichier!");
}


Parser::~Parser(void)
{
}
