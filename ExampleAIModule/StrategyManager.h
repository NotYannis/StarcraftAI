#pragma once

#include "Common.h"
#include "WorkerManager.h"

class StrategyManager
{
public:
	Unit cargo;


	StrategyManager();
	~StrategyManager();

	static StrategyManager & Instance();

	void Start();
	void Update();
};

