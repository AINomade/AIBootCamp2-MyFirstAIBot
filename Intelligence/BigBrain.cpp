#include "BigBrain.h"
BigBrain::BigBrain() {};
BigBrain::BigBrain(Graphe graphe, SInitData data) :model(graphe) {
	for_each(model._sommets.begin(), model._sommets.end(), [&](const Sommet goal) {
		if (goal._info.type == Goal) goals.push_back(goal);
		});

	SetBots(data);

	SetCheminsBots();
};

void BigBrain::SetCheminsBots() {
	for(int i =0;i<Bots.size();i++){
	//for_each(Bots.begin(), Bots.end(), [&](Bot bot) {
		int scoreBestChemin = 9999;
		vector<Sommet> bestChemin;
		Sommet goal1;

		
		for_each(goals.begin(), goals.end(), [&](Sommet goal) {
			bool goalLibre = true;
			for_each(Bots.begin(), Bots.end(), [&](Bot bot) {
				if (bot.goal == goal)goalLibre = false;
				});
			if (goalLibre) {
				AlphaStar AS(model, Bots[i].start, goal);
				AS.VisiterLesSommets();
				if (AS.chemin.size() < scoreBestChemin) {
					bestChemin = AS.chemin;
					scoreBestChemin = bestChemin.size();
					goal1 = goal;
				}
			}
			});
		Bots[i].goal = goal1;
		Bots[i].chemin = bestChemin;
	}//);
};


void BigBrain::SetBots(SInitData data) {
	for_each(model._sommets.begin(), model._sommets.end(), [&](const Sommet start) {
		for (int j = 0; j < data.nbNPCs; j++) {
			if (start._info.q == data.npcInfoArray[j].q && start._info.r == data.npcInfoArray[j].r) {
				Bot npc(data.npcInfoArray[j], start);
				Bots.push_back(npc);
			}
		}
	});
};