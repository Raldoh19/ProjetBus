#include "Solution.h"
#include <algorithm>
using namespace std;

Solution::Solution()
{
}
Solution::~Solution()
{
}
Solution::Solution(vector<Vehicule> vehicules, ListePlaces parking)
{
	this->vehiculesConcernes = vehicules;
	this->etatParking = parking;
}

ListePlaces Solution::nouveauParking(Date dateDebut, Date dateFin)
{
	ListePlaces nouveauParking = this->etatParking;
	for(int i=0;i< this->vehiculesConcernes.size(); i++)
		vehiculesConcernes[i].afficherMissions();
	nouveauParking.afficher();

	while(!dateDebut.estEgale(dateFin))
	{
		dateDebut.ajouterMinute(1);
		if(dateDebut.estEgale(dateFin))
			cout << "this is the end" << endl;
	}
	return nouveauParking;
}

bool Solution::verificationSolution(ListePlaces parkingInitial, Date dateInitiale, Date dateFin)
{
	/*
	Date dateCourante = dateInitiale;
	vector<pair<Vehicule*,int>> vehiculesABouger;
	Vehicule* pBusEnCours;
	unsigned int index,indexMission;
	int idMission;

	while(dateCourante.estAvant(dateFin)){
		vehiculesABouger = chercheBusADeplacer(dateCourante);
		if(vehiculesABouger.size() > 0){
			for(index = 0; index < vehiculesABouger.size(); index++){
				pBusEnCours = vehiculesABouger.at(index).first;
				idMission = vehiculesABouger.at(index).second;
				//CAS DE DEPART D'UN BUS 
				if(pBusEnCours->getMissions().at(idMission).getDateDepart == dateCourante){
					//Verifier si etatParking->listePlaces.at(NumDePlacesPourSortir) == -1
				}
				//CAS D'ARRIVEE D'UN BUS
				else{
					//Plus dur :((((((
				}
			
			}

		}
	
		dateCourante.ajouterMinute(1);
	}
	*/
	return true;
}

//Methode qui renvoie un vecteur qui contient des couples (adresse de vehicule, entier)
//											adresse de vehicule = l'adresse du vehicule qui doit bouger
//											entier = ID de la mission qui le fait bouger
vector<pair<Vehicule*,int>> Solution::chercheBusADeplacer(Date date)
{
	vector<pair<Vehicule*,int>> listeDesVehicules;
	/*unsigned int indexVehicules,indexMission;
	//Pour tous les vehicules concernes
	for(indexVehicules = 0; indexVehicules <this->vehiculesConcernes.size(); indexVehicules++){
		//pour chaque mission
		for(indexMission = 0; indexMission < vehiculesConcernes[indexVehicules].getNbMissions();indexMission++){
			//si l'heure de depart/arrive correspond a l'heure en cours, alors il va falloir deplacer le bus
			if(vehiculesConcernes[indexVehicules].getMissions().at(indexMission).getDateArrivee().estEgale(date) || vehiculesConcernes[indexVehicules].getMissions().at(indexMission).getDateDepart().estEgale(date)){
				listeDesVehicules.push_back(make_pair(&vehiculesConcernes[indexVehicules],indexMission));
			}
		}
	}*/
	return listeDesVehicules;
}
