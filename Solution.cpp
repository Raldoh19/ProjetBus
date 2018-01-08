#include "Solution.h"
#include "Place.h"

using namespace std;
/*
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
}*/

bool Solution::pourraPartir(Place p,Date date){
	unsigned int i,j;
	

	for(i = 0; i < p.getPlaceSortie()->getNbPlaces(); i++){
		Vehicule busConcerne = vehiculesConcernes[p.getPlaceSortie()->getListePlaces()[i]->getNumeroVehicule()];
		for(j = 0;j < busConcerne.getNbMissions() ; j++){
			if(!busConcerne.getMissions()[j].getDateDepart().estAvant(date)){
				return false;
			}
		}
	}
	return true;
}

std::vector<Caracteristique> Solution::getCaracteristiques(){
	return caracteristiques;
}

bool Solution::verificationSolution(Solution solution,ListePlaces parking){
	//Avancer dans les caracteristiques de la solution à partir du parking initial, et voir si on viole des contraintes
	unsigned int indexCarac;
	Place* placeAVerif;
	/*
	- Il faut trouver l'ordre d'arrives des bus
		On tri solution.caracteristiques en fonction des dates d'arrivees
	- On parcourt les caracteristiques, et on regarde si l'assignation est bonne 
		PeutSeGarer a la place
		PeutPartirDeLaPlace à temps
	*/
	vector<Caracteristique> caracteristiquesTriees = solution.trierCaracteristiques(solution.getCaracteristiques());
	for(indexCarac = 0; indexCarac < caracteristiquesTriees.size(); indexCarac++){
		placeAVerif = parking.getPlace(caracteristiquesTriees.at(indexCarac).getNumeroPlace());
		//Si jamais on retombe sur le meme numero de bus, il faut l'enlever de se precedente place
		unsigned int i =0;
		while(i < parking.getListePlaces().size() && parking.getListePlaces()[i]->getNumeroVehicule() != caracteristiquesTriees[indexCarac].getIdVehicule()){
			i++;
		}
		if(i != parking.getListePlaces().size()){
			//On a trouve une place avec notre vehicule deja gare,on le retire
			parking.getListePlaces()[i]->setNumeroVehicule(-1);
		}

		//-------Verification que la place est bien vide------------------
		if(placeAVerif->getNumeroVehicule() == -1){
			//Place VIDE
		}else{
			//PLACE NON VIDE
			std::cout<<"--VERIFICATION SOLUTION-- PLACE OCCUPEE vehicule"<< caracteristiquesTriees[indexCarac].getIdVehicule() << "place "<< placeAVerif->getNumeroPlace()<<endl;
		}
		//-----------------------------------------------------------------
		//------Verification que l'on peut acceder a la place--------------
		if(placeAVerif->peutAcceder()){
			//Place ACCESSIBLE
		}else{
			//Place NON ACCESSIBLE
			std::cout<<"--VERIFICATION SOLUTION-- PLACE IMPOSSIBLE D'ACCES vehicule"<< caracteristiquesTriees[indexCarac].getIdVehicule() << "place "<< placeAVerif->getNumeroPlace()<<endl;
		}
		//-----------------------------------------------------------------
		//------Verification que le bus pourra partir----------------------
		//On suppose que l'indice du bus = id du bus && 
		Vehicule busAVerif = vehiculesConcernes[caracteristiquesTriees[indexCarac].getIdVehicule()];
		Date dateProchainDepart = busAVerif.premierDepartApres(caracteristiquesTriees[indexCarac].getDateArrivee());
		//prendre + proche DateDepart apres carac.dateArrivee pour le bus a verif
		//Verifier qu'il pourra partir apres cette date
		if( pourraPartir(*placeAVerif,dateProchainDepart) ){
			//Bus POURRA partir
		}else{
			//ne POURRA PAS partir
			std::cout<<"--VERIFICATION SOLUTION-- PLACE DONT LE BUS NE POURRA PAS PARTIR vehicule"<< caracteristiquesTriees[indexCarac].getIdVehicule() << "place "<< placeAVerif->getNumeroPlace()<<endl;
		}
		//-----------------------------------------------------------------
		//On place quand meme le vehicule pour continuer d'avancer avec ces caracteristiques
		placeAVerif->setNumeroVehicule(caracteristiquesTriees.at(indexCarac).getIdVehicule());
	}

	return true;
}


std::vector<Caracteristique> Solution::trierCaracteristiques(std::vector<Caracteristique> caracteristiques){
	std::vector<Caracteristique> caracTriee;
	unsigned int i,indiceMin;
	
	while(caracteristiques.size() > 0){
		indiceMin = 0;
		for(i = 0; i < caracteristiques.size();i++){
			if(caracteristiques[i].getDateArrivee().estAvant(caracteristiques[indiceMin].getDateArrivee())){
				indiceMin = i;
			}
		}
		caracTriee.push_back(caracteristiques[indiceMin]);
		caracteristiques.erase(caracteristiques.begin()+indiceMin);
	}
	return caracTriee;
}
/*
	Methodes TODO : 
		- void placesEligibles(vector<string>* placesVides) : modifie placesVides pour ne garder que les places où l'on peut se garer.
		Comment savoir si le bus pourra partir ? il faut regarder les places de sortie, si elle est occupée, voir si le bus dessus a une mission avec dateDepart avant la prochaine mission du bus qui se gare
		un beau petit bordel quoi :(((((((((
		*/

/*
	recupere les places auxquels on peut accéder
*/
void Solution::placesEligibles(vector<string>* placesVide){
	unsigned int i;
	
	Place* placeAVerif;

	for(i = 0; i < placesVide->size(); i++){
		placeAVerif = trouverPlaceNumero(placesVide->at(i));
		if(placeAVerif != NULL){
			if(placeAVerif->peutAcceder()){

			}
		}
	}
}




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


Place* Solution::trouverPlaceNumero(string numero){
	unsigned int i = 0;

	while(i < etatParking.getNbPlaces()){
		if(etatParking.getListePlaces().at(i)->getNumeroPlace().compare(numero) == 0){
			return etatParking.getListePlaces().at(i);
		}
		i++;
	}
	return NULL;
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

