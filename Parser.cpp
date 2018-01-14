#include "Parser.h"
#include "Place.h"
#include <fstream>
#include <iostream>
#include <algorithm>

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

Parser::Parser(string file)
{
	this->file= file;
}

/**
Methode qui genere le parking et lie les différentes places au véhicules/missions ainsi qu'au trajet pour y acceder/sortir
*/
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
						parking->ajouterPlace(new Place(ligneDecoupe[0], stoi(ligneDecoupe[1]), stoi(ligneDecoupe[2])));
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
		this->generateTrajet(*parking);
		// On assigne les missions au bus, chaque bus aura ses missions du jour
		int indexMissions = 0;
		while(indexMissions < missions.size())
		{
			for(int i = 0 ; i < buses.size(); i++)
			{
				buses[i]->ajouterMission(missions[indexMissions]);
				indexMissions++;
				if(indexMissions < missions.size())
				{
					while(missions[indexMissions].getDateDepart().estApres(missions[indexMissions-1].getDateArrivee()))
					{
						buses[i]->ajouterMission(missions[indexMissions]);
						indexMissions++;
						if(indexMissions >= missions.size())
							break;
					}
				}
				if(indexMissions >= missions.size())
					break;
			}
			// On decalle le reste des missions d'un jour pour les reattribuer
			for(int k = indexMissions; k < missions.size(); k++)
				missions[k].plusOneDay();
		}
		// On trie les places par rapport a leur proximite de la sortie
		parking->triListe();
		// On trie les bus par rapport a leur premiere mission
		sort(buses.begin(), buses.end(), [ ]( Vehicule* first, Vehicule* second )
		{
		   	if(first->getMissions().size() == 0 || second->getMissions().size() == 0)
				return true;
			return first->getMissions()[0] < second->getMissions()[0];
		});

		// On supprime les bus qui sont deja stationnés
		vector<Vehicule> busAaffecter;
		for(int i = 0 ; i < buses.size(); i++)
		{
			busAaffecter.push_back(*(buses[i]));
		}
		for(int i = 0 ; i < parking->getListePlaces().size(); i++)
		{
			int numVehicule = parking->getListePlaces()[i]->getNumeroVehicule();
			if(numVehicule != -1)
			{
				int j = 0;
				for(j = 0; j < busAaffecter.size() ; j++)
					if(busAaffecter[j].getID() == numVehicule)
						break;
				busAaffecter.erase(busAaffecter.begin()+j);
			}
		}
		// On doit affecter au bus non stationné les places proche de la sortie
		
		int indexPlace = 0;
		for(int i = 0; i < busAaffecter.size(); i++)
		{
			Place * placeVide = parking->getPlaceVide(busAaffecter[i].getTailleVehicule())->getPlaceIndex(0);
			if(placeVide)
			{
				std::string numPlaceVide = placeVide->getNumeroPlace();
				parking->getPlace(numPlaceVide)->setNumeroVehicule(busAaffecter[i].getID());
			}
		}
		return parking;
	}
	else throw new exception("[Parking] Impossible d'ouvrir le fichier!");
}

/**
Methode qui genere les vehicules
*/
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

/**
Methode qui genere les missions de tout les bus
*/
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


/**
Methode qui genere le trajet pour acceder ou sortir a une place
*/
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
					Place * placeConcerne = parking.getPlace(ligneDecoupe[0]);
					if(placeConcerne)
					{
						string ES = ligneDecoupe[2];
						ListePlaces * trajetPlace = new ListePlaces();
						vector<string> placeDecoupe;
						int nombrePlace = split(placeDecoupe, ligneDecoupe[1],',');
						for(int i = 0;i < nombrePlace;i++)
						{
							try
							{
								Place * placeGenere = parking.getPlace(placeDecoupe[i]);
								if(placeGenere)
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