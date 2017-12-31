#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "Vehicule.h"
#include "ListePlaces.h"

class Solution
{
private:
	std::vector<Vehicule> vehiculesConcernes;
	ListePlaces etatParking;
public:
	Solution(void);
	Solution(std::vector<Vehicule>, ListePlaces);
	~Solution(void);

	ListePlaces nouveauParking(Date dateDebut, Date dateFin);
	bool verificationSolution(ListePlaces parkingInitial, Date dateInitiale,Date dateFin);
	std::vector<std::pair<Vehicule*,int>> chercheBusADeplacer(Date date);

};

#endif