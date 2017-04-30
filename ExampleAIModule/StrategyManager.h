#pragma once

#include "Common.h"
#include "OrderQueue.h"
#include "WorkerManager.h"
#include "BuildingManager.h"

class StrategyManager
{
public:
	Unit cargo;
	BaseCard * workingCards;

	OrderQueue * orderQueue;
	WorkerManager * workerManager;

	int * workingCardsCount;

	StrategyManager();
	~StrategyManager();

	static StrategyManager & Instance();

	void Start();
	void Update();
	void CardDone(BaseCard * c);
};