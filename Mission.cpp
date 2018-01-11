#include "Mission.h"
#include <iostream>
#include <fstream>

using namespace std; 

Mission::Mission()
{

}

Mission::Mission(int id, Date dateArr, Date dateDep)
{
	this->ID = id;
	if(dateArr.estApres(dateDep))
	{
		dateArrivee = dateArr;
		dateDepart = dateDep;
	}
	else
	{
		dateArrivee = dateDep;
		dateDepart = dateArr;
	}
}

Mission::~Mission()
{
}

int Mission::getID()
{
	return ID;
}

Date Mission::getDateArrivee()
{
	return dateArrivee;
}
	
Date Mission::getDateDepart()
{
	return dateDepart;
}

bool Mission::operator<(const Mission& mission)
{
	return this->dateDepart.estAvant(mission.dateDepart);
}

void Mission::afficher()
{
	std::cout << 
		"\t\t[" << ID << "]" << std::endl << 
		"\tDate debut: " << dateDepart.toString() << std::endl <<
		"\tDate arrivee : " << dateArrivee.toString() << std::endl;
}

void Mission::generateMissions(int nbVehicule, Date dateDebut, Date dateFin)
{
	std::vector<Mission> missionToReturn;
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
			dateDebutMission.ajouterMinute(minuteRandDebut);

			// Génération aléatoire de la fin de la mission
			Date dateFinMission = dateDebutMission;
			int heureRandFin = rand() % 3 + 2;
			int minuteRandFin = rand() % 59;
			dateFinMission.ajouterHeure(heureRandFin);
			dateFinMission.ajouterMinute(minuteRandFin);

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
	ofstream fichier("F:\\ProjetVisualStudio\\ProjetBus\\ProjetBus\\Debug\\DonneesBus\\entrees_volume\\Mission.csv", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
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
