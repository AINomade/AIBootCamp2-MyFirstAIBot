#include "MyBotLogic.h"

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


MyBotLogic::MyBotLogic()
{
	//Write Code Here
}

MyBotLogic::~MyBotLogic()
{
	//Write Code Here

}

void MyBotLogic::Configure(const SConfigData& _configData)
{
#ifdef BOT_LOGIC_DEBUG
	mLogger.Init(_configData.logpath, "MyBotLogic.log");
#endif

	BOT_LOGIC_LOG(mLogger, "Configure", true);

	//Write Code Here
}

void MyBotLogic::Init(const SInitData& _initData)
{	
	BOT_LOGIC_LOG(mLogger, "Init", true);
	/*Affiche les cases*/
	auto tiles = _initData.tileInfoArray;

	for_each(tiles + 0, tiles + _initData.tileInfoArraySize, [&](const STileInfo& tile) {
		BOT_LOGIC_LOG(mLogger, "Affiche les cases" , true);
		BOT_LOGIC_LOG(mLogger, "TILE(" + to_string(tile.q) + ", " + to_string(tile.r) + ") > type: " + to_string(tile.type), true);
		});
	/*FIN Affiche les cases*/

	/*Init Graphe*/
	Graphe modelInit(_initData);
	BOT_LOGIC_LOG(mLogger, "Model", true);
	BOT_LOGIC_LOG(mLogger, modelInit.ToString(), true);
	/*Fin Init Graphe*/

	/*Init BigBrain*/
	BB = BigBrain (modelInit, _initData);
	/*Fin Init BigBrain*/
}

void MyBotLogic::GetTurnOrders(const STurnData& _turnData, std::list<SOrder>& _orders)
{
	BOT_LOGIC_LOG(mLogger, "GetTurnOrders", true);
	/*for_each(BB.Bots.begin(), BB.Bots.end(), [&](Bot bot) {
		_orders.push_back(bot.GetTurnOrder());
	});
	BOT_LOGIC_LOG(mLogger, to_string(BB.Bots[0].pos), true);*/
	
	//for (int i = 0; i < BB.Bots.size(); i++) {
	for (int i = BB.Bots.size()-1; i >=0; i--) {
		bool peutAvancer = true;
		if (!BB.Bots[i].arrive) {
			for_each(BB.Bots.begin(), BB.Bots.end(), [&](Bot bot) {
				if (bot.id != BB.Bots[i].id && bot.chemin[bot.pos] == BB.Bots[i].chemin[BB.Bots[i].pos + 1]) peutAvancer = false;
				});
			if (peutAvancer) { BOT_LOGIC_LOG(mLogger, "Bot ID : "+ to_string(BB.Bots[i].id)+" move to "+ BB.Bots[i].chemin[BB.Bots[i].pos + 1].ToString(), true);  _orders.push_back(BB.Bots[i].GetTurnOrder()); }
		}
	}

}