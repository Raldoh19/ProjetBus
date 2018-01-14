#include "Generateur.h"
#include "Place.h"
#include <ctime>
#include <fstream>

/**
Constructeur pour le generateur, on lui indique le dossier ou devront se situer les generations
*/
Generateur::Generateur(string file)
{
	this->file= file;
}

/**
	Methode qui genere des missions entre une plage horaire pour un nombre de vehicule précisé
*/
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
	ofstream fichier(this->file+"Mission.csv", ios::out | ios::trunc);
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

/**
	Methode qui genere un fichier parking
*/
void Generateur::generateParkingFile(ListePlaces parking)
{
	// Ecriture dans le fichier
	ofstream fichier(this->file+"Emplacement.csv", ios::out | ios::trunc);
    if(fichier)
    {
		for(int i = 0 ; i < parking.getNbPlaces(); i++)
		{
			Place * currentPlace = parking.getPlaceIndex(i);
			// ON DOIT AVOIR 30% de grande place et 20% de petites
			double pourcentage = (double)i/parking.getNbPlaces();
			if(pourcentage <= 0.7)
				currentPlace->setTaillePlace(2);
			else
				currentPlace->setTaillePlace(3);

			fichier << currentPlace->getNumeroPlace() << ";" << currentPlace->getTaillePlace() << ";\n"; 
		}
        fichier.close();
    }
    else
		cerr << "Impossible d'ouvrir le fichier !" << endl;

	ofstream fichier2(this->file+"Trajet.csv", ios::out | ios::trunc);
    if(fichier2)
    {
		for(int i = 0 ; i < parking.getNbPlaces(); i++)
		{
			Place * currentPlace = parking.getPlaceIndex(i);
			for(int t = 0 ; t < currentPlace->getPlaceAcces().size() ; t++)
			{
				std::string generatedStringAcces = "";
				for(int k= 0 ; k < currentPlace->getPlaceAcces()[t]->getNbPlaces(); k++)
				{
					generatedStringAcces = generatedStringAcces.append(currentPlace->getPlaceAcces()[t]->getPlaceIndex(k)->getNumeroPlace());
					if(k != currentPlace->getPlaceAcces()[t]->getNbPlaces() - 1)
						generatedStringAcces = generatedStringAcces.append(",");
				}
				fichier2 << currentPlace->getNumeroPlace() << ";" << generatedStringAcces << ";E\n";
			}

			for(int t = 0 ; t < currentPlace->getPlaceSortie().size() ; t++)
			{
				std::string generatedStringSortie = "";
				for(int k= 0 ; k < currentPlace->getPlaceSortie()[t]->getNbPlaces(); k++)
				{
					generatedStringSortie = generatedStringSortie.append(currentPlace->getPlaceSortie()[t]->getPlaceIndex(k)->getNumeroPlace());
					if(k != currentPlace->getPlaceSortie()[t]->getNbPlaces() - 1)
						generatedStringSortie = generatedStringSortie.append(",");
				}
				fichier2 << currentPlace->getNumeroPlace() << ";" << generatedStringSortie << ";S\n";
			}
		}
        fichier2.close();
    }
    else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}
/**
	Methode qui genere un parking de type A pour un nombre de place et de colonnes précis.
*/
void Generateur::generateParkingA(int nombrePlace, int nbColonne)
{
	int nbLigne = nombrePlace / nbColonne;
	ListePlaces parking;
	for(int j = 0 ; j < nbColonne; j++)
	{
		ListePlaces * placeColonnes = new ListePlaces();
		for(int i = 0 ; i < nbLigne ; i++)
		{
			placeColonnes->ajouterPlace(new Place(std::to_string(j).append(std::to_string(i)).append("P"), 0));
		}
		for(int indexPlace = 0 ; indexPlace < placeColonnes->getNbPlaces() ; indexPlace++)
		{
			Place * currentPlace = placeColonnes->getPlaceIndex(indexPlace);
			ListePlaces * cheminAcces = placeColonnes->subList(0, indexPlace);
			ListePlaces * cheminSortie = placeColonnes->subList(indexPlace+1, placeColonnes->getNbPlaces());
			if(cheminAcces)
				currentPlace->setPlaceAcces(cheminAcces);
			if(cheminSortie)
				currentPlace->setPlaceSortie(cheminSortie);
			parking.ajouterPlace(currentPlace);
		}
	}
	this->generateParkingFile(parking);
}

/**
Methode qui genere des bus et les stock dans un fichier */
void Generateur::generateVehicules(int nbVehicule)
{
	std::vector<Vehicule> vehiculeToReturn;

	for(int i = 0; i < nbVehicule ; i++)
	{
		// ON DOIT AVOIR 30% de grand bus et 70% de petit
		double pourcentage = i/(double)nbVehicule;
		if(pourcentage <= 0.7)
			vehiculeToReturn.push_back(Vehicule(i, 2));
		else
			vehiculeToReturn.push_back(Vehicule(i, 3));
	}
	// Ecriture dans le fichier
	ofstream fichier(this->file+"Vehicule.csv", ios::out | ios::trunc);
    if(fichier)
    {
		for(int i = 0 ; i < vehiculeToReturn.size(); i++)
		{
			fichier << vehiculeToReturn[i].getID() <<";;" << vehiculeToReturn[i].getTailleVehicule() <<";0;0;;;\n";
		}
        fichier.close();
    }
    else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}

void Generateur::generateParkingB5(int nbColonne)
{
	ListePlaces parking;
	for(int i = 0 ; i < nbColonne ;i++)
	{
		ListePlaces * placeColonnes = new ListePlaces();
		for(int j = 0; j < 5; j++)
			placeColonnes->ajouterPlace(new Place(std::to_string(j).append("P").append(std::to_string(i)), 0));

		for(int indexPlace = 0 ; indexPlace < placeColonnes->getNbPlaces() ; indexPlace++)
		{
			Place * currentPlace = placeColonnes->getPlaceIndex(indexPlace);
			if(indexPlace == 0)
			{
				ListePlaces * cheminSortie1 = new ListePlaces();
				cheminSortie1->ajouterPlace(placeColonnes->getPlaceIndex(2));
				cheminSortie1->ajouterPlace(placeColonnes->getPlaceIndex(4));
				currentPlace->setPlaceSortie(cheminSortie1);

				ListePlaces * cheminSortie2 = new ListePlaces();
				cheminSortie2->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminSortie2->ajouterPlace(placeColonnes->getPlaceIndex(4));
				currentPlace->setPlaceSortie(cheminSortie2);
			}
			else if(indexPlace == 1)
			{
				ListePlaces * cheminSortie1 = new ListePlaces();
				cheminSortie1->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminSortie1->ajouterPlace(placeColonnes->getPlaceIndex(4));
				currentPlace->setPlaceSortie(cheminSortie1);
			}
			else if(indexPlace == 2)
			{
				ListePlaces * cheminAcces1 = new ListePlaces();
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(0));
				currentPlace->setPlaceAcces(cheminAcces1);

				ListePlaces * cheminSortie1 = new ListePlaces();
				cheminSortie1->ajouterPlace(placeColonnes->getPlaceIndex(4));
				currentPlace->setPlaceSortie(cheminSortie1);
			}
			else if(indexPlace == 3)
			{
				ListePlaces * cheminAcces1 = new ListePlaces();
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(0));
				currentPlace->setPlaceAcces(cheminAcces1);

				ListePlaces * cheminAcces2 = new ListePlaces();
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(1));
				currentPlace->setPlaceAcces(cheminAcces2);

				ListePlaces * cheminSortie1 = new ListePlaces();
				cheminSortie1->ajouterPlace(placeColonnes->getPlaceIndex(4));
				currentPlace->setPlaceSortie(cheminSortie1);
			}
			else if(indexPlace == 4)
			{
				ListePlaces * cheminAcces1 = new ListePlaces();
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(2));
				currentPlace->setPlaceAcces(cheminAcces1);

				ListePlaces * cheminAcces2 = new ListePlaces();
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(3));
				currentPlace->setPlaceAcces(cheminAcces2);

				ListePlaces * cheminAcces3 = new ListePlaces();
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(1));
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(3));
				currentPlace->setPlaceAcces(cheminAcces3);
			}
			parking.ajouterPlace(currentPlace);
		}
	}
	this->generateParkingFile(parking);
}

void Generateur::generateParkingB10(int nbColonne)
{
	ListePlaces parking;
	for(int i = 0 ; i < nbColonne ;i++)
	{
		ListePlaces * placeColonnes = new ListePlaces();

		for(int j = 0; j < 10; j++)
			placeColonnes->ajouterPlace(new Place(std::to_string(j).append("P").append(std::to_string(i)), 0));

		for(int indexPlace = 0 ; indexPlace < placeColonnes->getNbPlaces() ; indexPlace++)
		{
			Place * currentPlace = placeColonnes->getPlaceIndex(indexPlace);
			if(indexPlace == 0)
			{
				// 2 -> 4 -> 6 -> 8
				ListePlaces * cheminSortie1 = new ListePlaces();
				cheminSortie1->ajouterPlace(placeColonnes->getPlaceIndex(2));
				cheminSortie1->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminSortie1->ajouterPlace(placeColonnes->getPlaceIndex(6));
				cheminSortie1->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie1);
				// 2-> 4 -> 7 -> 8
				ListePlaces * cheminSortie2 = new ListePlaces();
				cheminSortie2->ajouterPlace(placeColonnes->getPlaceIndex(2));
				cheminSortie2->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminSortie2->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie2->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie2);
				// 2 -> 4 -> 7 -> 9
				ListePlaces * cheminSortie3 = new ListePlaces();
				cheminSortie3->ajouterPlace(placeColonnes->getPlaceIndex(2));
				cheminSortie3->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminSortie3->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie3->ajouterPlace(placeColonnes->getPlaceIndex(9));
				currentPlace->setPlaceSortie(cheminSortie3);
				// 3 -> 4 -> 7 -> 8
				ListePlaces * cheminSortie4 = new ListePlaces();
				cheminSortie4->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminSortie4->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminSortie4->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie4->ajouterPlace(placeColonnes->getPlaceIndex(9));
				currentPlace->setPlaceSortie(cheminSortie4);
				// 3 -> 4 -> 7 -> 9
				ListePlaces * cheminSortie8 = new ListePlaces();
				cheminSortie8->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminSortie8->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminSortie8->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie8->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie8);
				// 3 -> 4 -> 6
				ListePlaces * cheminSortie6 = new ListePlaces();
				cheminSortie6->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminSortie6->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminSortie6->ajouterPlace(placeColonnes->getPlaceIndex(6));
				cheminSortie6->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie6);
				// 3 -> 5 -> 7 -> 8
				ListePlaces * cheminSortie7 = new ListePlaces();
				cheminSortie7->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminSortie7->ajouterPlace(placeColonnes->getPlaceIndex(5));
				cheminSortie7->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie7->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie7);
				// 3 -> 5 -> 7 -> 9
				ListePlaces * cheminSortie5 = new ListePlaces();
				cheminSortie5->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminSortie5->ajouterPlace(placeColonnes->getPlaceIndex(5));
				cheminSortie5->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie5->ajouterPlace(placeColonnes->getPlaceIndex(9));
				currentPlace->setPlaceSortie(cheminSortie5);


			}
			else if(indexPlace == 1)
			{
				// 3 -> 4 -> 7 -> 8
				ListePlaces * cheminSortie4 = new ListePlaces();
				cheminSortie4->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminSortie4->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminSortie4->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie4->ajouterPlace(placeColonnes->getPlaceIndex(9));
				currentPlace->setPlaceSortie(cheminSortie4);
				// 3 -> 4 -> 7 -> 9
				ListePlaces * cheminSortie8 = new ListePlaces();
				cheminSortie8->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminSortie8->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminSortie8->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie8->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie8);
				// 3 -> 4 -> 6
				ListePlaces * cheminSortie6 = new ListePlaces();
				cheminSortie6->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminSortie6->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminSortie6->ajouterPlace(placeColonnes->getPlaceIndex(6));
				cheminSortie6->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie6);
				// 3 -> 5 -> 7 -> 8
				ListePlaces * cheminSortie7 = new ListePlaces();
				cheminSortie7->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminSortie7->ajouterPlace(placeColonnes->getPlaceIndex(5));
				cheminSortie7->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie7->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie7);
				// 3 -> 5 -> 7 -> 9
				ListePlaces * cheminSortie5 = new ListePlaces();
				cheminSortie5->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminSortie5->ajouterPlace(placeColonnes->getPlaceIndex(5));
				cheminSortie5->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie5->ajouterPlace(placeColonnes->getPlaceIndex(9));
				currentPlace->setPlaceSortie(cheminSortie5);
			}
			else if(indexPlace == 2)
			{
				// 4 -> 6 -> 8
				ListePlaces * cheminSortie1 = new ListePlaces();
				cheminSortie1->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminSortie1->ajouterPlace(placeColonnes->getPlaceIndex(6));
				cheminSortie1->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie1);
				// 4 -> 7 -> 8
				ListePlaces * cheminSortie2 = new ListePlaces();
				cheminSortie2->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminSortie2->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie2->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie2);
				// 4 -> 7 -> 9
				ListePlaces * cheminSortie3 = new ListePlaces();
				cheminSortie3->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminSortie3->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie3->ajouterPlace(placeColonnes->getPlaceIndex(9));
				currentPlace->setPlaceSortie(cheminSortie3);

				ListePlaces * cheminAcces1 = new ListePlaces();
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(0));
				currentPlace->setPlaceAcces(cheminAcces1);
			}
			else if(indexPlace == 3)
			{
				// 3 -> 4 -> 7 -> 8
				ListePlaces * cheminSortie4 = new ListePlaces();
				cheminSortie4->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminSortie4->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie4->ajouterPlace(placeColonnes->getPlaceIndex(9));
				currentPlace->setPlaceSortie(cheminSortie4);
				// 3 -> 4 -> 7 -> 9
				ListePlaces * cheminSortie8 = new ListePlaces();
				cheminSortie8->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminSortie8->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie8->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie8);
				// 3 -> 4 -> 6
				ListePlaces * cheminSortie6 = new ListePlaces();
				cheminSortie6->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminSortie6->ajouterPlace(placeColonnes->getPlaceIndex(6));
				cheminSortie6->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie6);
				// 3 -> 5 -> 7 -> 8
				ListePlaces * cheminSortie7 = new ListePlaces();
				cheminSortie7->ajouterPlace(placeColonnes->getPlaceIndex(5));
				cheminSortie7->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie7->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie7);
				// 3 -> 5 -> 7 -> 9
				ListePlaces * cheminSortie5 = new ListePlaces();
				cheminSortie5->ajouterPlace(placeColonnes->getPlaceIndex(5));
				cheminSortie5->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie5->ajouterPlace(placeColonnes->getPlaceIndex(9));
				currentPlace->setPlaceSortie(cheminSortie5);

				ListePlaces * cheminAcces1 = new ListePlaces();
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(0));
				currentPlace->setPlaceAcces(cheminAcces1);

				ListePlaces * cheminAcces2 = new ListePlaces();
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(1));
				currentPlace->setPlaceAcces(cheminAcces2);
			}
			else if(indexPlace == 4)
			{
				// 4 -> 7 -> 9
				ListePlaces * cheminSortie4 = new ListePlaces();
				cheminSortie4->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie4->ajouterPlace(placeColonnes->getPlaceIndex(9));
				currentPlace->setPlaceSortie(cheminSortie4);
				// 3 -> 4 -> 7 -> 9
				ListePlaces * cheminSortie8 = new ListePlaces();
				cheminSortie8->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie8->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie8);
				// 3 -> 4 -> 6
				ListePlaces * cheminSortie6 = new ListePlaces();
				cheminSortie6->ajouterPlace(placeColonnes->getPlaceIndex(6));
				cheminSortie6->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie6);

				ListePlaces * cheminAcces1 = new ListePlaces();
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(3));
				currentPlace->setPlaceAcces(cheminAcces1);

				ListePlaces * cheminAcces2 = new ListePlaces();
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(1));
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(3));
				currentPlace->setPlaceAcces(cheminAcces2);

				ListePlaces * cheminAcces3 = new ListePlaces();
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(2));
				currentPlace->setPlaceAcces(cheminAcces3);
			}
			else if(indexPlace == 5)
			{
				ListePlaces * cheminSortie7 = new ListePlaces();
				cheminSortie7->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie7->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie7);
				// 3 -> 5 -> 7 -> 9
				ListePlaces * cheminSortie5 = new ListePlaces();
				cheminSortie5->ajouterPlace(placeColonnes->getPlaceIndex(7));
				cheminSortie5->ajouterPlace(placeColonnes->getPlaceIndex(9));
				currentPlace->setPlaceSortie(cheminSortie5);

				
				ListePlaces * cheminAcces1 = new ListePlaces();
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(3));
				currentPlace->setPlaceAcces(cheminAcces1);

				ListePlaces * cheminAcces2 = new ListePlaces();
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(1));
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(3));
				currentPlace->setPlaceAcces(cheminAcces2);

			}
			else if(indexPlace == 6)
			{
				ListePlaces * cheminSortie8 = new ListePlaces();
				cheminSortie8->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie8);

				ListePlaces * cheminAcces1 = new ListePlaces();
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(2));
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(4));
				currentPlace->setPlaceAcces(cheminAcces1);

				ListePlaces * cheminAcces2 = new ListePlaces();
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(1));
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(4));
				currentPlace->setPlaceAcces(cheminAcces2);

				ListePlaces * cheminAcces3 = new ListePlaces();
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(4));
				currentPlace->setPlaceAcces(cheminAcces3);
			}
			else if(indexPlace == 7)
			{
				ListePlaces * cheminSortie4 = new ListePlaces();
				cheminSortie4->ajouterPlace(placeColonnes->getPlaceIndex(9));
				currentPlace->setPlaceSortie(cheminSortie4);

				ListePlaces * cheminSortie8 = new ListePlaces();
				cheminSortie8->ajouterPlace(placeColonnes->getPlaceIndex(8));
				currentPlace->setPlaceSortie(cheminSortie8);

				ListePlaces * cheminAcces1 = new ListePlaces();
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(2));
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(4));
				currentPlace->setPlaceAcces(cheminAcces1);

				ListePlaces * cheminAcces2 = new ListePlaces();
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(1));
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(5));
				currentPlace->setPlaceAcces(cheminAcces2);

				ListePlaces * cheminAcces3 = new ListePlaces();
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(4));
				currentPlace->setPlaceAcces(cheminAcces3);

				ListePlaces * cheminAcces4 = new ListePlaces();
				cheminAcces4->ajouterPlace(placeColonnes->getPlaceIndex(1));
				cheminAcces4->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminAcces4->ajouterPlace(placeColonnes->getPlaceIndex(4));
				currentPlace->setPlaceAcces(cheminAcces4);

			}
			else if(indexPlace == 8)
			{
				ListePlaces * cheminAcces1 = new ListePlaces();
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(2));
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(6));
				currentPlace->setPlaceAcces(cheminAcces1);

				ListePlaces * cheminAcces2 = new ListePlaces();
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(2));
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(7));
				currentPlace->setPlaceAcces(cheminAcces2);

				ListePlaces * cheminAcces3 = new ListePlaces();
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(6));
				currentPlace->setPlaceAcces(cheminAcces3);

				ListePlaces * cheminAcces4 = new ListePlaces();
				cheminAcces4->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces4->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminAcces4->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminAcces4->ajouterPlace(placeColonnes->getPlaceIndex(7));
				currentPlace->setPlaceAcces(cheminAcces4);

				ListePlaces * cheminAcces5 = new ListePlaces();
				cheminAcces5->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces5->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminAcces5->ajouterPlace(placeColonnes->getPlaceIndex(5));
				cheminAcces5->ajouterPlace(placeColonnes->getPlaceIndex(7));
				currentPlace->setPlaceAcces(cheminAcces5);

				ListePlaces * cheminAcces6 = new ListePlaces();
				cheminAcces6->ajouterPlace(placeColonnes->getPlaceIndex(1));
				cheminAcces6->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminAcces6->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminAcces6->ajouterPlace(placeColonnes->getPlaceIndex(6));
				currentPlace->setPlaceAcces(cheminAcces6);

				ListePlaces * cheminAcces7 = new ListePlaces();
				cheminAcces7->ajouterPlace(placeColonnes->getPlaceIndex(1));
				cheminAcces7->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminAcces7->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminAcces7->ajouterPlace(placeColonnes->getPlaceIndex(7));
				currentPlace->setPlaceAcces(cheminAcces7);

				ListePlaces * cheminAcces8 = new ListePlaces();
				cheminAcces8->ajouterPlace(placeColonnes->getPlaceIndex(1));
				cheminAcces8->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminAcces8->ajouterPlace(placeColonnes->getPlaceIndex(5));
				cheminAcces8->ajouterPlace(placeColonnes->getPlaceIndex(7));
				currentPlace->setPlaceAcces(cheminAcces8);
			}
			else if(indexPlace == 9)
			{
				ListePlaces * cheminAcces1 = new ListePlaces();
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(2));
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminAcces1->ajouterPlace(placeColonnes->getPlaceIndex(7));
				currentPlace->setPlaceAcces(cheminAcces1);

				ListePlaces * cheminAcces2 = new ListePlaces();
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminAcces2->ajouterPlace(placeColonnes->getPlaceIndex(7));
				currentPlace->setPlaceAcces(cheminAcces2);

				ListePlaces * cheminAcces3 = new ListePlaces();
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(0));
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(5));
				cheminAcces3->ajouterPlace(placeColonnes->getPlaceIndex(7));
				currentPlace->setPlaceAcces(cheminAcces3);

				ListePlaces * cheminAcces4 = new ListePlaces();
				cheminAcces4->ajouterPlace(placeColonnes->getPlaceIndex(1));
				cheminAcces4->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminAcces4->ajouterPlace(placeColonnes->getPlaceIndex(4));
				cheminAcces4->ajouterPlace(placeColonnes->getPlaceIndex(7));
				currentPlace->setPlaceAcces(cheminAcces4);

				ListePlaces * cheminAcces5 = new ListePlaces();
				cheminAcces5->ajouterPlace(placeColonnes->getPlaceIndex(1));
				cheminAcces5->ajouterPlace(placeColonnes->getPlaceIndex(3));
				cheminAcces5->ajouterPlace(placeColonnes->getPlaceIndex(5));
				cheminAcces5->ajouterPlace(placeColonnes->getPlaceIndex(7));
				currentPlace->setPlaceAcces(cheminAcces5);
			}
			parking.ajouterPlace(currentPlace);
		}
	}
	this->generateParkingFile(parking);
}