#include "Bot.h"


Bot::Bot(SNPCInfo data, Sommet start) :id(data.uid), pos(0), start(start), arrive(false) {};

SOrder Bot::GetTurnOrder() {
	SOrder ordre;
	if (!(chemin[pos] == goal)) {
		int q = chemin[pos + 1]._info.q - chemin[pos]._info.q;
		int r = chemin[pos + 1]._info.r - chemin[pos]._info.r;
		int coor = 10 * q + r;
		switch (coor) {
		case (-10):
			ordre.direction = NW;
			break;
		case (-9):
			ordre.direction = NE;
			break;
		case (1):
			ordre.direction = E;
			break;
		case (10):
			ordre.direction = SE;
			break;
		case (9):
			ordre.direction = SW;
			break;
		case (-1):
			ordre.direction = W;
			break;
		case (0):
			ordre.direction = CENTER;
			break;
		}
		ordre.orderType = Move;
		ordre.npcUID = id;
		//ordre.objectUID = _turnData.objectInfoArray->uid;
		ordre.interactionType = SearchHiddenDoor;
		pos++;
		if (chemin[pos]==goal) arrive = true;
		return ordre;
	}
	
	else {
		ordre.orderType = Move;
		ordre.npcUID = id;
		//ordre.objectUID = _turnData.objectInfoArray->uid;
		ordre.interactionType = SearchHiddenDoor;
		return ordre;
	}
};
