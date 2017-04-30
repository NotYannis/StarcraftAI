#include "StrategyManager.h"

StrategyManager::StrategyManager()
{
	workingCards = new BaseCard[100]; workingCardsCount = 0;
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
			workerManager->SetWorker(u, workerManager->workersCristal, workerManager->wCristalsCount);
		}
	}

	Broodwar << "Number of Gas Workers : "		<< *workerManager->wGasCount << std::endl;
	Broodwar << "Number of Cristal Workers : "	<< *workerManager->wCristalsCount << std::endl;
	Broodwar << "Number of Builders Workers : "	<< *workerManager->wBuildersCount << std::endl;
	Broodwar << "Number of Idle Workers : "		<< *workerManager->wIdlesCount << std::endl;
	Broodwar << "Number of Scout Workers : "	<< *workerManager->wScoutsCount << std::endl;

	int priority = 1;
	for each (TilePosition tilePosition in Broodwar->getStartLocations())
	{
		if (tilePosition != Broodwar->self()->getStartLocation()) {

			ScoutCard scoutCard = ScoutCard(priority,
				*workerManager->GetClosestWorker(cargo, workerManager->workersCristal, workerManager->wCristalsCount),
				(Position)tilePosition);

			orderQueue->AddCard(scoutCard, orderQueue->scoutCards, orderQueue->scoutCardsCount);
			++priority;

		}
	}

	Broodwar << "Number of Scout Cards : " << *orderQueue->scoutCardsCount << std::endl;

	Position pylonPos = (Position)Broodwar->getBuildLocation(UnitTypes::Protoss_Pylon, cargo->getTilePosition());
	
	BuildCard buildCard = BuildCard(20,
		*workerManager->GetClosestWorker(pylonPos, workerManager->workersCristal, workerManager->wCristalsCount),
		UnitTypes::Protoss_Pylon, Broodwar->getBuildLocation(UnitTypes::Protoss_Pylon, cargo->getTilePosition()));

	orderQueue->AddCard(buildCard, orderQueue->buildCards, orderQueue->buildCardsCount);

	Broodwar << "Number of Build Cards : " << *orderQueue->buildCardsCount << std::endl;

}

void StrategyManager::Update(){
	//WorkerManager::Instance().HandleWorkerScout();
	//WorkerManager::Instance().HandleWorkersBuilder();
	WorkerManager::Instance().HandleWorkersCristal();
	//BuildingManager::Instance().GetNextCard();
}

void StrategyManager::CardDone(BaseCard * card) {
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
