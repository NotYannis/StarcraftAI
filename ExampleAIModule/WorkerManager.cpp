#include "WorkerManager.h"
#include "StrategyManager.h"
int cpt = 0;
WorkerManager::WorkerManager()
{
	workersGas = new Unit[20];		wGasCount = new int(0);
	workersCristal = new Unit[60];	wCristalCount = new int(0);
	workersBuilder = new Unit[10];	wBuilderCount = new int(0);
	workersIdle = new Unit[50];		wIdleCount = new int(0);
	workersScout = new Unit[10];	wScoutCount = new int(0);

	orderQueue = &OrderQueue::Instance();
}


WorkerManager::~WorkerManager()
{
	delete[] workersGas;	 delete wGasCount;
	delete[] workersCristal; delete wCristalCount;
	delete[] workersBuilder; delete wBuilderCount;
	delete[] workersIdle;	 delete wIdleCount;
	delete[] workersScout;	 delete wScoutCount;

	delete orderQueue;
}

WorkerManager & WorkerManager::Instance()
{
	static WorkerManager instance;
	return instance;
}

///<summary>Get the closest worker in the given array from the given position</summary>
Unit WorkerManager::GetClosestWorker(PositionOrUnit pos, Unit * workersList, int * workersCount) {
	double distance = 20000;
	Unit u;
	int index = 0;

	//Search for the nearest worker 
	for (int i = 0; i < *workersCount; ++i){
		if (workersList[i]->getDistance(pos) < distance){
			distance = workersList[i]->getDistance(pos);
			u = workersList[i];
			index = i;
		}
	}

	return u;
}

///<summary>Remove the worker in the given array</summary>
void WorkerManager::RemoveWorker(Unit u, Unit * workersList, int * workersCount) {
	int found = false;

	//Search for the nearest worker 
	for (int i = 0; i < *workersCount; ++i) {
		if (workersList[i] == u) {
			found = true;
		}
		if (found){
			workersList[i] = workersList[i + 1];
		}
	}

	--*workersCount;
}

///<summary>Set a worker in the given array</summary>
void WorkerManager::AddWorker(Unit u, Unit * workersList, int * workersCount) {
	workersList[*workersCount] = u;
	++*workersCount;
}

///<summary>Search a worker in the given array</summary>
bool WorkerManager::SearchWorker(Unit u, Unit * workersList, int * workersCount) {
	for (int i = 0; i < *workersCount; ++i) {
		if (workersList[i] == u) {
			return true;
		}
	}
	return false;
}

void WorkerManager::HandleWorkersIdle() {
	for (auto &u : Broodwar->self()->getUnits()) {
		if (!u->exists()) {
			continue;
		}
		if (u->getType().isWorker()) {
			if (u->isIdle()){
				workersIdle[*wIdleCount] = u;
				++*wIdleCount;
			}
		}
	}
}

void WorkerManager::HandleWorkersCristal() {
	for (int i = 0; i < *wCristalCount; ++i) {
		if (workersCristal[i]->isIdle()) {
			if (workersCristal[i]->isCarryingMinerals()) {
				workersCristal[i]->returnCargo();
			}
			else
			{
				workersCristal[i]->gather(workersCristal[i]->getClosestUnit(IsMineralField));
			}
		}
	}
}

void WorkerManager::HandleWorkersGas() {
	for (int i = 0; i < *wGasCount; ++i) {
		if (workersGas[i]->isCarryingGas()) {
			workersGas[i]->returnCargo();
		}
		else if (!workersGas[i]->getPowerUp()) {
			workersGas[i]->gather(workersGas[i]->getClosestUnit(IsRefinery));
		}
	}
}

void WorkerManager::HandleWorkerScout() {
	if (*orderQueue->scoutCardsCount > 0) {
		//Broodwar << "Number of Scout Cards : " << *orderQueue->scoutCardsCount << std::endl;
		ScoutCard * c = orderQueue->GetHighestPriorityScoutCard();
		if (*wScoutCount > 0) {
			//Broodwar << "Number of Builder Workers : " << *wBuilderCount << std::endl;
			for (int i = 0; i < *wScoutCount; ++i) {
				if (workersScout[i]->isIdle()) {

					/*Broodwar << "Priority : " << c->priority << std::endl;
					Broodwar << "Target : " << c->target << std::endl;
					Broodwar << "TilePosition : " << c->tilePosition << std::endl;
					Broodwar << "Mineral Price : " << c->mineralPrice << std::endl;
					Broodwar << "Gas Price : " << c->gasPrice << std::endl;*/

					if (workersScout[i]->getPosition() != c->target) {
						workersScout[i]->move(c->target);
						c->onUse = true;
					}
					else {
						orderQueue->RemoveScoutCard(c);
					}
				}
			}
		}
		else if (*wCristalCount > 0) {
			Unit u = GetClosestWorker(c->target, workersCristal, wCristalCount);
			//Broodwar << u << std::endl;
			u->stop();
			RemoveWorker(u, workersCristal, wCristalCount);
			AddWorker(u, workersScout, wScoutCount);
		}
	}
}

void WorkerManager::HandleWorkersBuilder() {
	if (*orderQueue->buildCardsCount > 0) {
		//Broodwar << "Number of Build Cards : " << *orderQueue->buildCardsCount << std::endl;
		BuildCard * c = orderQueue->GetHighestPriorityBuildCard();
		if (*wBuilderCount > 0) {
			//Broodwar << "Number of Builder Workers : " << *wBuilderCount << std::endl;
			for (int i = 0; i < *wBuilderCount; ++i) {
				if (workersBuilder[i]->isIdle()) {

					/*Broodwar << "Priority : " << c->priority << std::endl;
					Broodwar << "Target : " << c->target << std::endl;
					Broodwar << "TilePosition : " << c->tilePosition << std::endl;
					Broodwar << "Mineral Price : " << c->mineralPrice << std::endl;
					Broodwar << "Gas Price : " << c->gasPrice << std::endl;*/

					static int lastChecked = 0;

					if (lastChecked + 400 < Broodwar->getFrameCount() &&
						Broodwar->self()->incompleteUnitCount(c->target) == 0 &&
						!c->onUse && c->priority != -1 &&
						Broodwar->self()->gas() >= c->gasPrice &&
						Broodwar->self()->minerals() >= c->mineralPrice) { //ECHANGER CE IF AVEC CELUI DU DESSUS POUR NE PRENDRE UN WORKERCRISTAL QUE QD ON A LES RESSOURCES MAIS CA PLANTE DE OUFZER

						lastChecked = Broodwar->getFrameCount();
						//Broodwar << "Builder Workers currently Building" << std::endl;
						workersBuilder[i]->build(c->target, c->tilePosition);
						c->onUse = true;
						//IL FAUT REMOVE LA CARTE UNE FOIS QUE LE BUILDING COMMENCE A ETRE CONSTRUIT
						//orderQueue->RemoveBuildCard(c);
					}
				}
			}
		}
		else if (*wCristalCount > 0) {
			Unit u = GetClosestWorker((Position)c->tilePosition, workersCristal, wCristalCount);
			//Broodwar << u << std::endl;
			u->stop();
			RemoveWorker(u, workersCristal, wCristalCount);
			AddWorker(u, workersBuilder, wBuilderCount);
		}
	}
}

void WorkerManager::SetWorkerToJob(Unit u, Card * c){
	workersJob.insert(std::pair<Unit, Card * >(u, c));
}

void WorkerManager::removeCard(Unit u, Card * c){

}