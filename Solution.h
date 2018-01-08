#ifndef SOLUTION_H
#define SOLUTION_H

#include "Vehicule.h"
#include "ListePlaces.h"
#include "Caracteristique.h"
#include <string>
class Solution
{
private:
	Vehicule* vehiculesConcernes;
	unsigned int nbVehiculesConcernes;
	ListePlaces etatParking;
	std::vector<Caracteristique> caracteristiques;
public:
	Solution(void){}
	~Solution(void){}

	Solution(ListePlaces parking,Vehicule* vehicules,unsigned int nb){
		etatParking = parking;
		vehiculesConcernes = vehicules;
		nbVehiculesConcernes = nb;
	}


	ListePlaces nouveauParking();
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

	bool pourraPartir(Place p,Date date);
};
#endif;

