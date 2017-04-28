#pragma once
#include "common.h"
#include "CombatManager.h"

class WarManager
{
	int nbZealotInSquad;
	Unitset Gateways;
	std::vector<std::pair<Unit, int>>* nbZealotReadyPerGateway;
	Position enemyBase;

public:
	WarManager(int nzis, Position eb);
	~WarManager();
	void AddGateway(Unit u);
	void SendSquads();
	void CheckZealots(Unit u);
	void Update(Unit u);

};

