#pragma once

#include "Globals.h"
#include "ConfigData.h"
#include "InitData.h"
#include "TurnData.h"
#include <algorithm>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;

class Sommet {
public:

	int _id = -1;
	STileInfo _info{};
	int scoreAStare = 9999;
	vector<int> _suivant;

	Sommet() ;
	Sommet(int id, STileInfo info);

	void AddSuivant(vector<Sommet> sommets, SInitData turnData);

	int Distance2(Sommet goal) const;

	int EvaluationAStar(Sommet goal, int score);

	string ToString() const;

	vector<int> GetVoisins();

	bool operator==(Sommet const& a);
};