#pragma once
#pragma once
#include "Sommet.h"
class Graphe {
public:
	vector<Sommet> _sommets;

	Graphe();
	//Graphe(STurnData turnData);
	Graphe(SInitData turnData);

	string ToString();
};