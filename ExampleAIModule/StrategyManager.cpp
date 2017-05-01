#include "StrategyManager.h"

StrategyManager::StrategyManager()
{
	workingCards = new Card[100]; workingCardsCount = 0;
	orderQueue = &OrderQueue().Instance();
	workerManager = &WorkerManager().Instance();

	for (auto &u : Broodwar->self()->getUnits()) {
		if (u->getType().isResourceDepot()){
			cargo = u;
		}
	}
}


StrategyManager::~StrategyManager()
{
	delete[] workingCards;
	delete orderQueue;
	delete workerManager;
}

StrategyManager & StrategyManager::Instance() {
	static StrategyManager instance;
	return instance;
}



void StrategyManager::Start() {
	
	for (auto & u : Broodwar->self()->getUnits()) {
		if (u->getType().isWorker()) {
			workerManager->AddWorker(u, workerManager->workersCristal, workerManager->wCristalCount);
		}
	}

	Broodwar << "Number of Gas Workers : "		<< *workerManager->wGasCount << std::endl;
	Broodwar << "Number of Cristal Workers : "	<< *workerManager->wCristalCount << std::endl;
	Broodwar << "Number of Builder Workers : "	<< *workerManager->wBuilderCount << std::endl;
	Broodwar << "Number of Idle Workers : "		<< *workerManager->wIdleCount << std::endl;
	Broodwar << "Number of Scout Workers : "	<< *workerManager->wScoutCount << std::endl;

	int priority = 1;
	for each (TilePosition tilePosition in Broodwar->getStartLocations())
	{
		if (tilePosition != Broodwar->self()->getStartLocation()) {

			ScoutCard * scoutCard = new ScoutCard(priority, (Position)tilePosition);

			orderQueue->AddScoutCard(scoutCard);
			++priority;
		}
	}

	Broodwar << "Number of Scout Cards : " << *orderQueue->scoutCardsCount << std::endl;

	BuildCard * pylon = new BuildCard(20, UnitTypes::Protoss_Pylon, 
		Broodwar->getBuildLocation(UnitTypes::Protoss_Pylon, cargo->getTilePosition()));
	orderQueue->AddBuildCard(pylon);

	/*BuildCard * gateway = new BuildCard(19, UnitTypes::Protoss_Gateway,
		Broodwar->getBuildLocation(UnitTypes::Protoss_Gateway, cargo->getTilePosition()));
	orderQueue->AddBuildCard(gateway);*/

	Broodwar << "Number of Build Cards : " << *orderQueue->buildCardsCount << std::endl;

}

void StrategyManager::Update(){
	//SCOUT ET BUILD FONCTIONNENT SEPAREMENT MAIS PAS ENCORE ENSEMBLE
	//COMMENTER L'UN POUR TESTER L'AUTRE
	//workerManager->HandleWorkerScout();
	workerManager->HandleWorkersBuilder();
	workerManager->HandleWorkersCristal();
	//workerManager->HandleWorkersIdle();
	//BuildingManager::Instance().GetNextCard();
}

void StrategyManager::CardDone(Card * card) {
	bool found = false;

	for (int i = 0; i < *workingCardsCount; ++i) {
		if (!found) {
			if (workingCards[i] == *card) {
				found = true;
			}
		}
		else if (i < *workingCardsCount - 1) {
			workingCards[i] = workingCards[i + 1];
		}
	}

	--*workingCardsCount;
}
