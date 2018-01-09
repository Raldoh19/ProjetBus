#ifndef SOLUTION_H
#define SOLUTION_H

#include "Vehicule.h"
#include "ListePlaces.h"
#include "Caracteristique.h"
#include <string>
#include <vector>
class Solution
{
private:
	std::vector<Vehicule> vehiculesConcernes;
	ListePlaces etatParking;
	std::vector<Caracteristique> caracteristiques;
public:
	Solution(void){}
	~Solution(void){}

	Solution(ListePlaces parking,std::vector<Vehicule> vehicules)
	{
		etatParking = parking;
		vehiculesConcernes = vehicules;
	}

	void generateCarac();
	ListePlaces nouveauParking(Date dateDebut, Date dateFin);
	std::vector<Caracteristique> getCaracteristiques();
	std::vector<Caracteristique> trierCaracteristiques(std::vector<Caracteristique> caracteristiques);
	bool verificationSolution(Solution solution,ListePlaces parkingInitial);
	std::vector<std::pair<Vehicule*,int>> chercheBusADeplacer(Date date);
	std::vector<std::string> getPlacesVides(ListePlaces parking);
	bool peutSeGarer(Place p);
	bool peutPartir(Place p);
	int placeDuBus(int id);
	void placesEligibles(std::vector<std::string>* placesVide);
	Place* trouverPlaceNumero(std::string numero);
	bool peutSortirSolution(Place * p);
	bool pourraPartir(Place p,Date date);
	int getIdBus(int numero,std::vector<Vehicule> listeBus);
};
#endif;

