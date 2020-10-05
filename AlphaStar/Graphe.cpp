#include "Graphe.h"

Graphe::Graphe() {}
/*Graphe::Graphe(STurnData turnData) {
	auto tiles = turnData.tileInfoArray;
	int id = 0;
	for_each(tiles + 0, tiles + turnData.tileInfoArraySize, [&](const STileInfo& tile) {
		Sommet sommetTemp(id, tile);
		id += 1;
		_sommets.push_back(sommetTemp);
		});
	for_each(_sommets.begin(), _sommets.end(), [&](Sommet& sommet) {
		sommet.AddSuivant(_sommets, turnData);
		});
}*/
string Graphe::ToString() {
	string grapheText;
	for_each(_sommets.begin(), _sommets.end(), [&](const Sommet& sommet) {
		grapheText += sommet.ToString();
		});
	return grapheText;
}
Graphe::Graphe(SInitData turnData) {
	auto tiles = turnData.tileInfoArray;
	int id = 0;
	for_each(tiles + 0, tiles + turnData.tileInfoArraySize, [&](const STileInfo& tile) {
		Sommet sommetTemp(id, tile);
		id += 1;
		_sommets.push_back(sommetTemp);
		});
	for_each(_sommets.begin(), _sommets.end(), [&](Sommet& sommet) {
		sommet.AddSuivant(_sommets, turnData);
		});
}


