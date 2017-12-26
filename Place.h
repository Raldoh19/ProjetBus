#ifndef PLACE_H
#define PLACE_H
#include <string>

class ListePlaces;

using namespace std;

class Place
{
private:
	string numeroPlace;
	int taillePlace;
	int numeroVehicule;
	ListePlaces * placeAcces;
	ListePlaces * placeSortie;
public:
	Place();
	Place(string num,int taille);
	Place(string num,int taille, int numeroVehicule);
	~Place(void);
	string getNumeroPlace();
	void afficher();
	int getTaillePlace();
	int getNumeroVehicule();
	void setNumeroPlace(string num);
	void setTaillePlace(int taille);
	void setNumeroVehicule(int numeroVehicule);
};

#endif
