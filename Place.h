#ifndef PLACE_H
#define PLACE_H
#include <string>
#include <vector>

class ListePlaces;

using namespace std;

class Place
{
private:
	string numeroPlace;
	int taillePlace;
	int numeroVehicule;
	std::vector<ListePlaces*> placeAcces;
	std::vector<ListePlaces*> placeSortie;
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
	void setPlaceAcces(ListePlaces*);
	void setPlaceSortie(ListePlaces*);
	bool peutAcceder(int taille);
	bool peutSortir();
	std::vector<ListePlaces*> getPlaceAcces();
	std::vector<ListePlaces*> getPlaceSortie();

	bool operator<(Place& st);
};

#endif
