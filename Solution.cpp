#include "Solution.h"
#include "Place.h"
#include <algorithm>

using namespace std;

/**
	Constructeur de la solution, il prendra en paramètre:
	parking : le parking initial
	vehicules : les vehicules concernés par cette solution
*/
Solution::Solution(ListePlaces parking,std::vector<Vehicule> vehicules)
{
	etatParking = parking;
	vehiculesConcernes = vehicules;
}

/**
	Methode de verification de la solution prendra en paramètre:
	Une solution: Cette solution contient les caracteristiques et le parking final, on se servira de ces données pour voir si notre solution est correct.
	Parking : Le parking initial avant toutes itérations
	dateInitiale et dateFin : La plage horaire pour verifier cette solution
*/
bool Solution::verificationSolution(Solution solution,ListePlaces parking,Date dateInitiale,Date dateFin)
{
	int nombreTeleportation = 0;
	// ON VA LISTER TOUTES LES MISSIONS DU JOUR EN LES METTANT AVEC L'ID DU VEHICULE
	vector<std::pair<Vehicule,Mission>> allMissions;
	for(int i = 0 ; i < this->vehiculesConcernes.size() ; i++)
	{
		Vehicule currentVehicule = this->vehiculesConcernes[i];
		for(int j = 0 ; j < currentVehicule.getMissions().size() ; j++)
		{
			Mission currentMission = currentVehicule.getMissions()[j];
			allMissions.push_back(std::make_pair(currentVehicule,currentMission));
		}
	}

	// ON VA BOUCLER POUR TOUTE LA JOURNEE
	Date indexDebut = dateInitiale;
	for(dateInitiale; dateInitiale.estAvant(dateFin); dateInitiale.ajouterMinutes(1))
	{

		// On verifie que tout les vehicules peuvent sortir
		for(int i = 0 ; i < allMissions.size() ; i++)
		{
			if(allMissions[i].second.getDateDepart().estEgale(dateInitiale))
			{
				Place * placeVehicule = parking.getPlaceVehicule(allMissions[i].first.getID());
				if(placeVehicule)
				{
					if(!placeVehicule->peutSortir())
					{
						std::cout<<"--VERIFICATION SOLUTION-- TELEPORTATION vehicule " << placeVehicule->getNumeroVehicule() << " Place " << placeVehicule->getNumeroPlace() << std::endl;
						nombreTeleportation++;
					}
					placeVehicule->setNumeroVehicule(-1);
				}
				
			}
		}
		// On verifie que tout les vehicules peuvent acceder a leur place assigné
		for(int i = 0 ; i < allMissions.size() ; i++)
		{
			for(int j = 0; j < caracteristiques.size(); j++)
			{
				if(dateInitiale.estEgale(caracteristiques[j].getDateArrivee()) && (allMissions[i].second.getDateArrivee().estEgale(dateInitiale) ))
				{
					Vehicule infoVehicule(0,0);
					for(int indexVeh = 0; indexVeh < this->vehiculesConcernes.size() ; indexVeh++)
					{
						if(vehiculesConcernes[indexVeh].getID() == parking.getPlace(caracteristiques[j].getNumeroPlace())->getNumeroVehicule())
						{
							infoVehicule = vehiculesConcernes[indexVeh];
							break;
						}
					}

					if(parking.getPlace(caracteristiques[j].getNumeroPlace())->getNumeroVehicule() != -1 && parking.getPlace(caracteristiques[j].getNumeroPlace())->getNumeroVehicule() != caracteristiques[j].getIdVehicule())
					{
						std::cout<<"--VERIFICATION SOLUTION-- " << std::endl;
						std::cout<<"Impossible pour"<< caracteristiques[j].getIdVehicule() <<"d'acceder a " << caracteristiques[j].getNumeroPlace() << "[occupe par: "<< parking.getPlace(caracteristiques[j].getNumeroPlace())->getNumeroVehicule() <<"]" <<std::endl;
					}
					if(parking.getPlace(caracteristiques[j].getNumeroPlace())->getTaillePlace() < infoVehicule.getTailleVehicule() )
					{
						std::cout<<"--VERIFICATION SOLUTION-- Place " << caracteristiques[j].getNumeroPlace() << " de taille invalide ! " << std::endl;
					}

					parking.getPlace(caracteristiques[j].getNumeroPlace())->setNumeroVehicule(caracteristiques[j].getIdVehicule());
				}
			}
		}	
		if(dateInitiale.getHeures() == 23 && dateInitiale.getMinutes() == 59)
		{
			dateInitiale.ajouterJour(1);
			dateInitiale.setTime(0,0);
		}
	}
	return true;
}

/**
	Methode qui renvoie toute les places libre dans un parking donné
*/
vector<Place> Solution::getPlacesVides(ListePlaces parking)
{
	vector<Place> idPlacesVides;
	for(unsigned int i = 0; i < parking.getNbPlaces(); i++)
	{
		Place p = *(parking.getListePlaces()[i]);
		if(p.getNumeroVehicule() == -1){
			idPlacesVides.push_back(p);
		}
	}
	return idPlacesVides;
}

/**
	Algorithme qui renvoie l'état du parking au moment dateFin, et cela en générant des caractéristiques qui symbolisent les entrées au parking, tandis que les missions
	symbolisent les sorties
*/
ListePlaces Solution::nouveauParking(Date dateDebut, Date dateFin)
{
			
	int nombreTeleportation = 0;
	// ON VA LISTER TOUTES LES MISSIONS DU JOUR EN LES METTANT AVEC L'ID DU VEHICULE
	vector<std::pair<Vehicule,Mission>> allMissions;
	for(int i = 0 ; i < this->vehiculesConcernes.size() ; i++)
	{
		Vehicule currentVehicule = this->vehiculesConcernes[i];
		for(int j = 0 ; j < currentVehicule.getMissions().size() ; j++)
		{
			Mission currentMission = currentVehicule.getMissions()[j];
			allMissions.push_back(std::make_pair(currentVehicule,currentMission));
		}
	}
	// ON VA BOUCLER POUR TOUTE LA JOURNEE
	Date indexDebut = dateDebut;
	for(dateDebut; dateDebut.estAvant(dateFin); dateDebut.ajouterMinutes(1))
	{
		// On verifie pour tout les vehicules concernes par cette nouvelle solution
		for(int i = 0 ; i < allMissions.size() ; i++)
		{
			bool placeTrouvee = false;
			
			
			if(allMissions[i].second.getDateDepart().estEgale(dateDebut))
			{
				Place * placeVehicule = etatParking.getPlaceVehicule(allMissions[i].first.getID());
				if(placeVehicule)
				{
					if(!placeVehicule->peutSortir())
						nombreTeleportation++;
					placeVehicule->setNumeroVehicule(-1);
				}
			}
			if(allMissions[i].second.getDateArrivee().estEgale(dateDebut))
			{
				// UN VEHICULE SAPPRETE A ENTRER AU PARKING, IL FAUT AJOUTER UNE CARACTERISTIQUE AVEC SA NOUVELLE PLACE
				// ON OBTIENT UNE LISTE DE PLACE VIDE
				vector<Place> placeVide = getPlacesVides(etatParking);
				// ON TRIE LES PLACES PAR LES PLUS PROCHES DE LA SORTIE
				std::sort(placeVide.begin(), placeVide.end());
				// ON TEST SI ON PEUT ACCEDER A CETTE PLACE
				for(int k = 0; k < placeVide.size();k++)
				{
					Place * currentPlace = etatParking.getPlace(placeVide[k].getNumeroPlace());
					Vehicule infoVehicule(0,0);
					for(int indexVeh = 0; indexVeh < this->vehiculesConcernes.size() ; indexVeh++)
					{
						if(vehiculesConcernes[indexVeh].getID() == allMissions[i].first.getID())
						{
							infoVehicule = vehiculesConcernes[indexVeh];
							break;
						}
					}
					if(currentPlace->peutAcceder(infoVehicule.getTailleVehicule() ) && currentPlace->getNumeroVehicule() == -1)
					{
						this->caracteristiques.push_back(Caracteristique(allMissions[i].first.getID(),currentPlace->getNumeroPlace(), dateDebut));
						currentPlace->setNumeroVehicule(allMissions[i].first.getID());
						placeTrouvee = true;
						break;
					}
				}

			}
			if(placeTrouvee)
			{
				placeTrouvee = false;
				break;
			}
			
		}
		if(dateDebut.getHeures() == 23 && dateDebut.getMinutes() == 59)
		{
			dateDebut.ajouterJour(1);
			dateDebut.setTime(0,0);
		}
	}
	std::cout << "Solution trouve avec : " << nombreTeleportation << " teleportations, allez !" << std::endl;
	return etatParking;
}
