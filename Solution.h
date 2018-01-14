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
	Solution(ListePlaces parking,std::vector<Vehicule> vehicules);
	ListePlaces nouveauParking(Date dateDebut, Date dateFin);
	bool verificationSolution(Solution solution,ListePlaces parkingInitial,Date dateInitiale,Date dateFin);
	std::vector<Place> getPlacesVides(ListePlaces parking);
};
#endif;

