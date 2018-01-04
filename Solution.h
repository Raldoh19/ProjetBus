#ifndef SOLUTION_H
#define SOLUTION_H

#include "Vehicule.h"
#include "ListePlaces.h"
#include <string>
class Solution
{
private:
	Vehicule* vehiculesConcernes;
	unsigned int nbVehiculesConcernes;
	ListePlaces etatParking;
	
public:
	Solution(void){}
	~Solution(void){}

	Solution(ListePlaces parking){
		etatParking = parking;
	}

	ListePlaces nouveauParking();
	bool verificationSolution(ListePlaces parkingInitial, Date dateInitiale,Date dateFin);
	std::vector<std::pair<Vehicule*,int>> chercheBusADeplacer(Date date);
	std::vector<std::string> getPlacesVides(ListePlaces parking);
	bool peutSeGarer(Place p);
	bool peutPartir(Place p);
	int placeDuBus(int id);
};
#endif;
