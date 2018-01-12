#include "Generateur.h"
#include "Place.h"
#include <ctime>
#include <fstream>

Generateur::Generateur(string file)
{
	this->file= file;
}

void Generateur::generateMissions(int nbVehicule, Date dateDebut, Date dateFin)
{
	std::vector<Mission> missionToReturn;
	srand(time(NULL));
	Date realDateDebut = dateDebut;
	for(int i = 0; i < nbVehicule ; i++)
	{
		dateDebut = realDateDebut;
		while(dateDebut.estAvant(dateFin))
		{
			Date dateFinJour(dateDebut,23,59);

			// Génération aléatoire du début de la mission
			Date dateDebutMission = dateDebut;
			int heureRandDebut = rand() % 6;
			int minuteRandDebut = rand() % 59;
			dateDebutMission.ajouterHeure(heureRandDebut);
			dateDebutMission.ajouterMinutes(minuteRandDebut);

			// Génération aléatoire de la fin de la mission
			Date dateFinMission = dateDebutMission;
			int heureRandFin = rand() % 3 + 2;
			int minuteRandFin = rand() % 59;
			dateFinMission.ajouterHeure(heureRandFin);
			dateFinMission.ajouterMinutes(minuteRandFin);

			dateDebut = dateFinMission;
			// Si on arrive a la date dite "FIN JOUR", on reboucle.
			if(dateDebut.estApres(dateFinJour) || dateDebut.estEgale(dateFinJour))
				dateDebut.setTime(6,0);
			else
				// On cree une nouvelle mission
				missionToReturn.push_back(Mission(missionToReturn.size(),dateDebutMission,dateFinMission));
		}
	}
	// Ecriture dans le fichier
	ofstream fichier(this->file+"Mission.csv", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
    if(fichier)
    {
		for(int i = 0 ; i < missionToReturn.size(); i++)
		{

			fichier << i << ";" <<missionToReturn[i].getDateDepart().getHour() << ";" << missionToReturn[i].getDateArrivee().getHour() << ";0;120;GO;3;0;\n";
		}
        fichier.close();
    }
    else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}


void Generateur::generateParkingA(int nombrePlace, int nbColonne)
{
	int nbLigne = nombrePlace / nbColonne;
	ListePlaces parking;
	for(int j = 0 ; j < nbColonne; j++)
	{
		ListePlaces * placeColonnes = new ListePlaces();
		for(int i = 0 ; i < nbLigne ; i++)
		{
			// ON DOIT AVOIR 70% de grande place et 30% de petites
			double pourcentage = (double)i/nbLigne;
			if(pourcentage <= 0.7)
				placeColonnes->ajouterPlace(new Place(std::to_string(j).append(std::to_string(i)).append("P"), 3));
			else
				placeColonnes->ajouterPlace(new Place(std::to_string(j).append(std::to_string(i)).append("P"), 2));
		}
		for(int indexPlace = 0 ; indexPlace < placeColonnes->getNbPlaces() ; indexPlace++)
		{
			Place * currentPlace = placeColonnes->getPlaceIndex(indexPlace);
			ListePlaces * cheminAcces = placeColonnes->subList(0, indexPlace);
			ListePlaces * cheminSortie = placeColonnes->subList(indexPlace, placeColonnes->getNbPlaces());
			if(cheminAcces)
				currentPlace->setPlaceAcces(cheminAcces);
			if(cheminSortie)
				currentPlace->setPlaceSortie(cheminSortie);
			parking.ajouterPlace(currentPlace);
		}
	}
	parking.afficher();
}

void Generateur::generateParkingB(int nombrePlace,int nbColonne){
	int nbLigne = nombrePlace / nbColonne;
	ListePlaces parking;

}

Generateur::~Generateur(void)
{

}
