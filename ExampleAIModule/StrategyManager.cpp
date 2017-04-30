#include "StrategyManager.h"

StrategyManager::StrategyManager()
{
	workingCards = new Card[100]; workingCardsCount = 0;
	//orderQueue = &OrderQueue::Instance();
	//workerManager = &WorkerManager::Instance();

	for (auto &u : Broodwar->self()->getUnits()) {
		if (u->getType().isResourceDepot()){
			cargo = u;
		}
	}
}


StrategyManager::~StrategyManager()
{
	delete[] workingCards;
	//delete orderQueue;
	//delete workerManager;
}

StrategyManager & StrategyManager::Instance() {
	static StrategyManager instance;
	return instance;
}



void StrategyManager::Start() {
	WorkerManager workerManager = WorkerManager();

	int cptWorkers = 0;
	for (auto & u : Broodwar->self()->getUnits()){
		if (u->getType().isWorker()){
			workerManager.SetWorker(u, workerManager.workersCristal, workerManager.wCristalsCount);
			++cptWorkers;
		}
	}

	Broodwar << "Number of workers : " << cptWorkers << std::endl;
	Broodwar << "Number of cristal workers : " << workerManager.wCristalsCount << std::endl;
	Broodwar << "Number of gas workers : " << workerManager.wGasCount << std::endl;


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

	/*int priority = 1;
	for each (TilePosition tilePosition in Broodwar->getStartLocations())
	{
		if (tilePosition != Broodwar->self()->getStartLocation()) {
			CardScout scoutCard = CardScout(priority, WorkerManager::Instance().GetClosestWorkerCristal((Position)tilePosition),
				tilePosition);
			OrderQueue::Instance().AddCard(scoutCard, OrderQueue::Instance().scoutCards, OrderQueue::Instance().scoutCardsCount);
			++priority;
		}
	}*/

	/*CardBuild buildCard = CardBuild(20,
		WorkerManager::Instance().GetClosestWorkerCristal((Position)Broodwar->getBuildLocation(UnitTypes::Protoss_Pylon, cargo->getTilePosition())),
		(Position)Broodwar->getBuildLocation(UnitTypes::Protoss_Pylon, cargo->getTilePosition()), UnitTypes::Protoss_Pylon);

	OrderQueue::Instance().AddCard(buildCard, OrderQueue::Instance().buildCards, OrderQueue::Instance().buildCardsCount);*/

	//Broodwar << "Nb de cartes build : " << OrderQueue::Instance().buildCardsCount << std::endl;
	//Broodwar << "Nb de cartes scout : " << OrderQueue::Instance().scoutCardsCount << std::endl;

	/*Card c = Card(UnitTypes::Protoss_Pylon, 20, Broodwar->getBuildLocation(UnitTypes::Protoss_Pylon, cargo->getTilePosition()), false);
	Card d = Card(UnitTypes::Protoss_Gateway, 19, Broodwar->getBuildLocation(UnitTypes::Protoss_Gateway, TilePosition(0, 0)), false);
	Card e = Card(UnitTypes::Protoss_Pylon, 18, Broodwar->getBuildLocation(UnitTypes::Protoss_Pylon, cargo->getTilePosition()), false);

	OrderQueue::Instance().addCard(c);
	OrderQueue::Instance().addCard(d);
	OrderQueue::Instance().addCard(e);*/
}

void StrategyManager::Update() {
	/*WorkerManager::Instance().HandleWorkerScout();
	WorkerManager::Instance().HandleWorkersBuilder();*/
	//WorkerManager::Instance().HandleWorkersCristal();
	//BuildingManager::Instance().GetNextCard();
}

void StrategyManager::CardDone(Card * card) {
	bool found = false;

	for (int i = 0; i < workingCardsCount; ++i) {
		if (!found) {
			if (workingCards[i] == *card) {
				found = true;
			}
		}
		else if (i < workingCardsCount - 1) {
			workingCards[i] = workingCards[i + 1];
		}
	}

	--workingCardsCount;
}
