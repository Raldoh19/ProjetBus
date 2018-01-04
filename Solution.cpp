#include "Solution.h"
#include "Place.h"

using namespace std;
bool Solution::verificationSolution(ListePlaces parkingInitial, Date dateInitiale,Date dateFin){
	Date dateCourante = dateInitiale;
	vector<pair<Vehicule*,int>> vehiculesABouger;
	Vehicule* pBusEnCours;
	unsigned int index,indexMission;
	int idMission;

	while(dateCourante.estAvant(dateFin) || dateCourante.estEgale(dateFin)){
		//Plutot parcourir les places et voir celles qui ont un bus qui va arriver / partir ? 
		//si 2 bus doivent partir / arriver en meme temps il faut trouver un ordre pour qu'ils ne se bloquent pas
		vehiculesABouger = chercheBusADeplacer(dateCourante);
		if(vehiculesABouger.size() > 0){
			for(index = 0; index < vehiculesABouger.size(); index++){
				pBusEnCours = vehiculesABouger.at(index).first;
				idMission = vehiculesABouger.at(index).second;
				//CAS DE DEPART D'UN BUS 
				if(pBusEnCours->getMissions().at(idMission).getDateDepart().estEgale(dateCourante)){
					Place* placeEnCours = etatParking.getListePlaces().at(placeDuBus(pBusEnCours->getID()));
					if(peutPartir(*placeEnCours)){
						placeEnCours->setNumeroVehicule(-1);
					}
					
				}
				//CAS D'ARRIVEE D'UN BUS
				else{
					//Trouver la liste de toutes les places VIDES et ACCESSIBLES
					//				Parcourir le parking et recuperer la liste des places vides
					//				Pour toutes les places trouvees, regarder leur listeArrivee et regarder si elles sont toutes vides
					//Depuis cette liste, parcourir la liste des places pour partir de chaque place
					//Et verifier que si on lui assigne cette place, il pourra partir a sa prochaine mission
				}
			
			}

		}
	
		dateCourante.ajouterMinutes(1);
	}


	
	return true;
}



/*
	Methodes TODO : 
		- void placesEligibles(vector<string>* placesVides) : modifie placesVides pour ne garder que les places où l'on peut se garer.
		Comment savoir si le bus pourra partir ? il faut regarder les places de sortie, si elle est occupée, voir si le bus dessus a une mission avec dateDepart avant la prochaine mission du bus qui se gare
		un beau petit bordel quoi :(((((((((
		*/

int Solution::placeDuBus(int id){
	unsigned int i = 0;

	while(i < etatParking.getNbPlaces()){
		if(etatParking.getListePlaces().at(i)->getNumeroVehicule() == id){
			return i;
		}
		i++;
	}
	return -1;
}


/*
	Verifie qu'on peut partir de la place p
*/
bool Solution::peutPartir(Place p){
	int i=0;
	if(p.getPlaceSortie() == NULL){
		return true;
	}
	while(i < p.getPlaceSortie()->getNbPlaces()){
		if(p.getPlaceAcces()->getListePlaces().at(i)->getNumeroVehicule() != -1){
			return false;
		}
		i++;
	}
	return true;
}
/*
	Verifie qu'une place est accessible
*/
bool Solution::peutSeGarer(Place p){
	int i=0;
	if(p.getPlaceAcces() == NULL){
		return true;
	}
	while(i < p.getPlaceAcces()->getNbPlaces()){
		if(p.getPlaceAcces()->getListePlaces().at(i)->getNumeroVehicule() != -1){
			return false;
		}
		i++;
	}
	return true;
}
/*
	Parcours un parking, recupere les adresses des places vides de ce parking
*/
vector<string> Solution::getPlacesVides(ListePlaces parking){
	vector<string> idPlacesVides;
	unsigned int i;
	Place p;
	for(i = 0; i < parking.getNbPlaces(); i++){
		p = *parking.getListePlaces().at(i);
		if(p.getNumeroVehicule() == -1){
			idPlacesVides.push_back(p.getNumeroPlace());
		}
		
	}
	return idPlacesVides;
}


/*Methode qui renvoie un vecteur qui contient des couples (adresse de vehicule, entier)
										adresse de vehicule = l'adresse du vehicule qui doit bouger
										entier = ID de la mission qui le fait bouger
*/
vector<pair<Vehicule*,int>> Solution::chercheBusADeplacer(Date date){
	vector<pair<Vehicule*,int>> listeDesVehicules;
	unsigned int indexVehicules,indexMission;
	//Pour tous les vehicules concernes
	for(indexVehicules = 0; indexVehicules < nbVehiculesConcernes; indexVehicules++){
		//pour chaque mission
		for(indexMission = 0; indexMission < vehiculesConcernes[indexVehicules].getNbMissions();indexMission++){
			//si l'heure de depart/arrive correspond a l'heure en cours, alors il va falloir deplacer le bus
			if(vehiculesConcernes[indexVehicules].getMissions().at(indexMission).getDateArrivee().estEgale(date) || vehiculesConcernes[indexVehicules].getMissions().at(indexMission).getDateDepart().estEgale(date)){
				listeDesVehicules.push_back(make_pair(&vehiculesConcernes[indexVehicules],indexMission));
			}
		}
	}
	return listeDesVehicules;
}

