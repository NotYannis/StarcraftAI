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


	for each (TilePosition tilePosition in Broodwar->getStartLocations())
	{
		if (tilePosition != Broodwar->self()->getStartLocation()) {
			Card scoutCard = Card((Position)tilePosition, 10, false);
			OrderQueue::Instance().addCard(scoutCard);
		}
	}

	Card c = Card(UnitTypes::Protoss_Pylon, 20, Broodwar->getBuildLocation(UnitTypes::Protoss_Pylon, cargo->getTilePosition()), false);
	Card d = Card(UnitTypes::Protoss_Gateway, 15, Broodwar->getBuildLocation(UnitTypes::Protoss_Gateway, cargo->getTilePosition()), false);

	OrderQueue::Instance().addCard(c);
	OrderQueue::Instance().addCard(d);
}

void StrategyManager::Update(){
	//WorkerManager::Instance().HandleWorkerScout();
	WorkerManager::Instance().HandleWorkersBuilder();
	WorkerManager::Instance().HandleWorkersCristal();
	BuildingManager::Instance().GetNextCard();

	/*if (Broodwar->self()->minerals() >= UnitTypes::Protoss_Assimilator.mineralPrice() && WorkerManager::Instance().wBuildersCount == 0)
	{
		TilePosition gasTyle = Broodwar->getBuildLocation(UnitTypes::Protoss_Assimilator, cargo->getTilePosition());
		Unit u = WorkerManager::Instance().GetClosestWorkerCristal(Position(gasTyle.x, gasTyle.y));
		Card c = Card(UnitTypes::Protoss_Assimilator, 10, gasTyle, false, u);
		WorkerManager::Instance().SetWorkerToJob(u, c);
		WorkerManager::Instance().SetWorkerBuilder(u);
	}*/
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
