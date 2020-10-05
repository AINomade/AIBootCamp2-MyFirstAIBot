#include "AlphaStar.h"

AlphaStar::AlphaStar(Graphe g, Sommet start, Sommet goal) :actuel(start), start(start), graphe(g), score(0), goal(goal), iteration(0) {}
void AlphaStar::Visiter(int id) {
	Sommet s;
	for_each(graphe._sommets.begin(), graphe._sommets.end(), [&](const Sommet sommet) {
		if (sommet._id == id)s = sommet;
		});
	visite.push_back(make_pair(s.EvaluationAStar(goal, score), make_pair(s, actuel)));
}

void AlphaStar::MeilleurSommet() {
	Sommet mSommet;
	int mScore = 9999;
	for_each(visite.begin(), visite.end(), [&](const pair<int, pair<Sommet, Sommet>> pair) {
		if (pair.first < mScore && !(find(explore.begin(), explore.end(), pair.second.first._id) != explore.end())) {
			mSommet = pair.second.first;
			mScore = pair.first;
		}
		});
	actuel = mSommet;
	explore.push_back(actuel._id);
}

void AlphaStar::VisiteLesVoisins(Sommet s) {
	vector<int> voisins = s.GetVoisins();
	for_each(voisins.begin(), voisins.end(), [&](const int voisin) {
		Visiter(voisin);
		});
}

void AlphaStar::VisiterLesSommets() {
	if (!Finit() || iteration>graphe._sommets.size()) {
		VisiteLesVoisins(actuel);
		MeilleurSommet();
		VisiterLesSommets();
		iteration++;
	}
	else {
		Sommet iterateur = actuel;
		
		while (!(iterateur == start)) {
			chemin.insert(chemin.begin(), iterateur);
			auto it = find_if(visite.begin(), visite.end(), [&](pair<int, pair<Sommet, Sommet>>& precedent) {
				{return precedent.second.first == iterateur; }
				});
			pair<int, pair<Sommet, Sommet>> itpair = *it;

			iterateur = itpair.second.second;
		}
		chemin.insert(chemin.begin(), start);
	}
}

bool AlphaStar::Finit() {
	return actuel == goal;
}

string AlphaStar::ToString() {
	string cheminS = "";
	for_each(chemin.begin(), chemin.end(), [&](const Sommet sommet) {
		cheminS += sommet.ToString() + "  --->  ";
		});
	return cheminS;
}
