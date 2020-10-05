#pragma once
#include "graphe.h"

class AlphaStar {
	Graphe graphe;
	Sommet actuel;
	Sommet goal;
	Sommet start;
	vector<int> explore;
	vector<pair<int, pair<Sommet, Sommet>>> visite; // score sommet, sommet courant, sommet précédent
	int score;
	int iteration;
public:
	vector<Sommet> chemin;
	AlphaStar(Graphe g, Sommet start, Sommet goal);
	void Visiter(int id);
	void MeilleurSommet();
	void VisiteLesVoisins(Sommet s);
	void VisiterLesSommets();
	bool Finit();
	string ToString();
};