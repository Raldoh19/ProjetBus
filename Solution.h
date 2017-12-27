#ifndef SOLUTION_H
#define SOLUTION_H

#include "Vehicule.h"
#include "ListePlaces.h"

class Solution
{
private:
	Vehicule* vehiculesConcernes;
	unsigned int nbVehiculesConcernes;
	ListePlaces etatParking;
	
public:
	Solution(void){}
	~Solution(void){}

	ListePlaces nouveauParking();
	bool verificationSolution(ListePlaces parkingInitial, Date dateInitiale,Date dateFin);
	std::vector<pair<Vehicule*,int>> chercheBusADeplacer(Date date);
};
#endif;
