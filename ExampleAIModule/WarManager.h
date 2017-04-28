#pragma once
#include "common.h"
#include "CombatManager.h"

class WarManager
{
	int nbZealotInSquad;
	Unitset Gateways;
	std::vector<std::pair<Unit, int>>* nbZealotReadyPerGateway;
	std::vector<CombatManager>* squadsManager;
	Position enemyBase;
	bool found;

public:
	WarManager(int nzis);
	~WarManager();
	void AddGateway(Unit u);
	void SendSquads();
	void CheckZealots(Unit u);
	void Update(Unit u);
	void Update();
	void EnemyBaseFound(Position pos);

};

