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
	void OnBuildingCreate(UnitType u);
	void OnBuildingComplete(UnitType u);
};

