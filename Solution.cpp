#include "Solution.h"


bool Solution::verificationSolution(ListePlaces parkingInitial, Date dateInitiale,Date dateFin){
	Date dateCourante = dateInitiale;
	std::vector<Vehicule> vehiculesABouger;
	while(dateCourante.estAvant(dateFin)){
		vehiculesABouger = chercheBusADeplacer(dateCourante);
		if(vehiculesABouger.size() > 0){
			

		}

		/*
		Si un bus a une mission de depart / d'arrivee a dateCourante alors
			LE BUT est de soit le faire sortir soit le faire se garer
			Le faire sortir est assez simple, suffit de verifier qu'au moins 1 chemin pour sortir est vide de vehicules
			

		*/
	
	
	
	
		dateCourante.ajouterMinutes(1);
	}
	
	return true;
}

std::vector<Vehicule> Solution::chercheBusADeplacer(Date date){
	std::vector<Vehicule> listeDesVehicules;
	unsigned int indexVehicules,indexMission;
	//Pour tous les vehicules concernes
	for(indexVehicules = 0; indexVehicules < nbVehiculesConcernes; indexVehicules++){
		//pour chaque mission
		for(indexMission = 0; indexMission < vehiculesConcernes[indexVehicules].getNbMissions();indexMission++){
			//si l'heure de depart/arrive correspond a l'heure en cours, alors il va falloir deplacer le bus
			if(vehiculesConcernes[indexVehicules].getMissions().at(indexMission).getDateArrivee().estEgale(date) || vehiculesConcernes[indexVehicules].getMissions().at(indexMission).getDateDepart().estEgale(date)){
				listeDesVehicules.push_back(vehiculesConcernes[indexVehicules]);
			}
		}
	}
	return listeDesVehicules;
}

