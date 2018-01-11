#include "Solution.h"
#include "Place.h"
#include <algorithm>

using namespace std;

std::vector<Caracteristique> Solution::getCaracteristiques(){
	return caracteristiques;
}

bool Solution::verificationSolution(Solution solution,ListePlaces parking,Date dateInitiale){

	//Avancer dans les caracteristiques de la solution ‡ partir du parking initial, et voir si on viole des contraintes
	//Il faut REJOUER TOUT afin de faire partir les bus comme il faut
	//On a donc besoin en parametre : Solution, parking, DateDebut,DateFin
	//On doit regarder si ‡ heureEnCours un bus doit partir ou si un bus doit arriver (caracteristique)
	//Si un bus doit partir, on verifie qu'il peut, on signale s'il peut pas, et on le fait partir quand meme
	//Si un bus doit arriver, on verifie qu'il peut, on signale s'il peut pas, et on le fait se garer quand meme
	Date dateAvant = dateInitiale;
	unsigned int indexCarac;
	Place* placeAVerif;
	unsigned int i;
	/*
	- Il faut trouver l'ordre d'arrives des bus
		On tri solution.caracteristiques en fonction des dates d'arrivees
	- On parcourt les caracteristiques, et on regarde si l'assignation est bonne 
		PeutSeGarer a la place
		PeutPartirDeLaPlace √† temps
	*/
	vector<Caracteristique> caracteristiquesTriees = solution.trierCaracteristiques(solution.getCaracteristiques());
	
	for(indexCarac = 0; indexCarac < caracteristiquesTriees.size(); indexCarac++){
		Date dateCourante = caracteristiquesTriees[indexCarac].getDateArrivee();
		placeAVerif = parking.getPlace(caracteristiquesTriees.at(indexCarac).getNumeroPlace());
		
		//On fait partir les bus qui sont censÈ etre partis 
		for(i = 0; i < etatParking.getNbPlaces(); i++){
			if(etatParking.getListePlaces()[i]->getNumeroVehicule() != -1){
				Vehicule busGare = vehiculesConcernes[this->getIdBus(etatParking.getListePlaces()[i]->getNumeroVehicule(),vehiculesConcernes)];
				if(busGare.doitPartirEntre(dateAvant,dateCourante)){
					if(!etatParking.getListePlaces()[i]->peutSortir()){
						std::cout<<"--VERIFICATION SOLUTION-- TELEPORTATION POUR PARTIR vehicule " << busGare.getID() << " place " << etatParking.getListePlaces()[i]->getNumeroPlace() << std::endl;
					}
					etatParking.getListePlaces()[i]->setNumeroVehicule(-1);
				}
			}
		}

		//-------Verification que la place est bien vide------------------
		if(placeAVerif->getNumeroVehicule() == -1){
			//Place VIDE
		}else{
			//PLACE NON VIDE
			std::cout<<"--VERIFICATION SOLUTION-- PLACE OCCUPEE vehicule "<< caracteristiquesTriees[indexCarac].getIdVehicule() << " place "<< placeAVerif->getNumeroPlace()<<endl;
		}
		//-----------------------------------------------------------------
		//------Verification que l'on peut acceder a la place--------------
		if(placeAVerif->peutAcceder()){
			//Place ACCESSIBLE
		}else{
			//Place NON ACCESSIBLE
			std::cout<<"--VERIFICATION SOLUTION-- PLACE IMPOSSIBLE D'ACCES vehicule "<< caracteristiquesTriees[indexCarac].getIdVehicule() << " place "<< placeAVerif->getNumeroPlace()<<endl;
		}
		//-----------------------------------------------------------------
		//------Verification que le bus pourra partir----------------------
		int idBusAVerif = 0;
		while(idBusAVerif < vehiculesConcernes.size() && vehiculesConcernes[idBusAVerif].getID() != caracteristiquesTriees[indexCarac].getIdVehicule()){
			idBusAVerif++;
		}
		if(idBusAVerif != vehiculesConcernes.size()){
			Vehicule busAVerif = vehiculesConcernes[idBusAVerif];
			Date dateProchainDepart = busAVerif.premierDepartApres(caracteristiquesTriees[indexCarac].getDateArrivee());
			//prendre + proche DateDepart apres carac.dateArrivee pour le bus a verif
			//Verifier qu'il pourra partir apres cette date
			if( pourraPartir(*placeAVerif,dateProchainDepart) ){
				//Bus POURRA partir
			}else{
				//ne POURRA PAS partir
				std::cout<<"--VERIFICATION SOLUTION-- PLACE DONT LE BUS NE POURRA PAS PARTIR vehicule "<< caracteristiquesTriees[indexCarac].getIdVehicule() << " place "<< placeAVerif->getNumeroPlace()<<endl;
			}
		}else{
			cout<<"Pas trouve le bus dans les vehicules concernes."<<endl;
		}
		//-----------------------------------------------------------------
		//On place quand meme le vehicule pour continuer d'avancer avec ces caracteristiques
		placeAVerif->setNumeroVehicule(caracteristiquesTriees.at(indexCarac).getIdVehicule());
		//On met a jour l'heure
		dateAvant = dateCourante;
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
		- void placesEligibles(vector<string>* placesVides) : modifie placesVides pour ne garder que les places o√π l'on peut se garer.
		Comment savoir si le bus pourra partir ? il faut regarder les places de sortie, si elle est occup√©e, voir si le bus dessus a une mission avec dateDepart avant la prochaine mission du bus qui se gare
		un beau petit bordel quoi :(((((((((
		*/

/*
	recupere les places auxquels on peut acc√©der
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


/*Methode qui renvoie un vecteur qui contient des couples (adresse de vehicule, entier)
										adresse de vehicule = l'adresse du vehicule qui doit bouger
										entier = ID de la mission qui le fait bouger
*/
vector<pair<Vehicule*,int>> Solution::chercheBusADeplacer(Date date){
	vector<pair<Vehicule*,int>> listeDesVehicules;
	unsigned int indexVehicules,indexMission;
	//Pour tous les vehicules concernes
	for(indexVehicules = 0; indexVehicules < vehiculesConcernes.size(); indexVehicules++){
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




void Solution::generateCarac()
{
	// Generation des caracteristiques de la solution deja disponible
	for(int i = 0 ; i < etatParking.getNbPlaces() ; i++)
	{
		if(etatParking.getPlaceIndex(i)->getNumeroVehicule() != -1)
		{
			caracteristiques.push_back(Caracteristique(etatParking.getPlaceIndex(i)->getNumeroVehicule(), etatParking.getPlaceIndex(i)->getNumeroPlace(), Date(0,0,0,0,0)));
		}
	}
}


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
			if(allMissions[i].second.getDateDepart().estEgale(dateDebut))
			{
				Place * placeVehicule = etatParking.getPlaceVehicule(allMissions[i].first.getID());
				if(!placeVehicule->peutSortir()){
					std::cout<<"Je teleporte " << placeVehicule->getNumeroVehicule() <<std::endl;
					nombreTeleportation++;
				}
				
				placeVehicule->getPlaceSortie()->afficherSuite();
				//On vide la place
				placeVehicule->setNumeroVehicule(-1);
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
					if(currentPlace->peutAcceder() && currentPlace->getNumeroVehicule() == -1)
					{
						this->caracteristiques.push_back(Caracteristique(allMissions[i].first.getID(),currentPlace->getNumeroPlace(), dateDebut));
						currentPlace->setNumeroVehicule(allMissions[i].first.getID());
						break;
					}
				}
			}
		}
	}
	std::cout << "=== CARACTERISTIQUE GENERE ===" << std::endl;
	for(int z = 0 ; z < this->caracteristiques.size(); z++)
	{
		this->caracteristiques[z].toString();
	}
	std::cout << "Solution trouve avec : " << nombreTeleportation << " teleportations, allez !" << std::endl;
	return etatParking;
}

bool Solution::pourraPartir(Place p,Date date)
{
	unsigned int i,j;
	
	for(i = 0; i < p.getPlaceSortie()->getNbPlaces(); i++)
	{
		Place * currentPlace = p.getPlaceSortie()->getListePlaces()[i];
		int idBusConcerne = currentPlace->getNumeroVehicule();
		if(idBusConcerne == -1)
		{
			break;
		}

		Vehicule busConcerne = vehiculesConcernes.at(this->getIdBus(idBusConcerne,vehiculesConcernes));
		
		for(j = 0;j < busConcerne.getNbMissions() ; j++)
		{
			if(!busConcerne.getMissions()[j].getDateDepart().estAvant(date))
			{
				return false;
			}
		}
	}
	return true;
}

int Solution::getIdBus(int numero,vector<Vehicule> listeBus){
	int i = 0;

	while(i < listeBus.size()){
		if(numero == listeBus.at(i).getID()){
			return i;
		}
		i++;
	}
	return -1;
}
