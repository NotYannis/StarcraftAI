#pragma once

#include "Common.h"
#include "OrderQueue.h"
#include "WorkerManager.h"

class BuildingManager
{
public:
	int ressourcesNeeded;

	BuildingManager();
	~BuildingManager();
	static BuildingManager & Instance();


	void GetNextCard();
	void OnBuildingCreate(Unit u);
	void OnBuildingComplete(Unit u);
};

