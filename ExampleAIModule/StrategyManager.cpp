#include "StrategyManager.h"

StrategyManager::StrategyManager()
{
	workingCards = new Card[100]; workingCardsCount = 0;
	for (auto &u : Broodwar->self()->getUnits()){
		if (u->getType().isResourceDepot()){
			cargo = u;
		}
	}
}


StrategyManager::~StrategyManager()
{
	delete[] workingCards;
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

	/*Unit u = WorkerManager::Instance().GetClosestWorkerCristal(cargo);

	for each (TilePosition tilePosition in Broodwar->getStartLocations())
	{
		if (tilePosition != Broodwar->self()->getStartLocation()) {
			Card scoutingCard = Card((Position)tilePosition, 100, false, u);
			OrderQueue::Instance().addCard(scoutingCard);
		}
	}
	Card highestPrio = OrderQueue::Instance().getHighestPriority(scout);
	WorkerManager::Instance().SetWorkerToJob(u, highestPrio);
	WorkerManager::Instance().SetWorkerScout(u);*/

	Card c = Card(UnitTypes::Protoss_Pylon, 20, Broodwar->getBuildLocation(UnitTypes::Protoss_Pylon, cargo->getTilePosition()), false);
	Card d = Card(UnitTypes::Protoss_Gateway, 19, Broodwar->getBuildLocation(UnitTypes::Protoss_Gateway, TilePosition(0, 0)), false);
	Card e = Card(UnitTypes::Protoss_Pylon, 18, Broodwar->getBuildLocation(UnitTypes::Protoss_Pylon, cargo->getTilePosition()), false);

	OrderQueue::Instance().addCard(c);
	OrderQueue::Instance().addCard(d);
	OrderQueue::Instance().addCard(e);
}

void StrategyManager::Update(){
	WorkerManager::Instance().HandleWorkerScout();
	WorkerManager::Instance().HandleWorkersBuilder();
	WorkerManager::Instance().HandleWorkersCristal();
	BuildingManager::Instance().GetNextCard();
}

void StrategyManager::cardDone(Card * c){
	bool found = false;
	for (int i = 0; i < workingCardsCount; ++i){
		if (!found){
			if (workingCards[i] == *c){
				found = true;
			}
		}
		else if (i < workingCardsCount - 1){
			workingCards[i] = workingCards[i + 1];
		}
	}

	--workingCardsCount;
}
