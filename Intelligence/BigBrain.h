#pragma once
#include "AlphaStar/AlphaStar.h"
#include "Globals.h"
#include "Bot.h"
#include <list>

class BigBrain {
public:
	BigBrain();
	BigBrain(Graphe, SInitData);
	vector<Bot> Bots;
	Graphe model;
	vector<Sommet> goals;
	void SetCheminsBots();
	void SetBots(SInitData);
};