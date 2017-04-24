#include "StrategyManager.h"


StrategyManager::StrategyManager()
{
	for (auto &u : Broodwar->self()->getUnits()){
		if (u->getType().isResourceDepot())
			cargo = u;
		}
}


StrategyManager::~StrategyManager()
{
}

StrategyManager & StrategyManager::Instance(){
	static StrategyManager instance;
	return instance;
}



void StrategyManager::Start(){
	for (auto & u : Broodwar->self()->getUnits()){
		if (u->getType().isWorker()){
			WorkerManager::Instance().SetWorkerCristal(u);
		}
	}
}

void StrategyManager::Update(){
	WorkerManager::Instance().HandleWorkersCristal();
	//WorkerManager::Instance().HandleWorkersIdle();
}