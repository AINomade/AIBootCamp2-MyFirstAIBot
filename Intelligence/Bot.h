#pragma once
#include "AlphaStar/AlphaStar.h"
#include "Globals.h"
#include <list>

class Bot {
public:
	int id;
	int pos;
	Bot(SNPCInfo,Sommet);
	vector<Sommet> chemin;
	SOrder GetTurnOrder();
	Sommet start;
	Sommet goal;
	bool arrive;
};