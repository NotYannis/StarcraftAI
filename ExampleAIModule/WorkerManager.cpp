#include "WorkerManager.h"
#include "StrategyManager.h"


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
	for (int i = 0; i < *workersCount; ++i){
		if (workersList[i] == u){
			found = true;
		}
		if (found){
			workersList[i] = workersList[i + 1];
		}
	}

	--workersCount;
}

///<summary>Set a worker in the given array</summary>
void WorkerManager::SetWorker(Unit u, Unit * workersList, int * workersCount) {
	workersList[*workersCount] = u;
	++*workersCount;
}

void WorkerManager::HandleWorkersIdle() {
	for (auto &u : Broodwar->self()->getUnits()) {
		if (!u->exists()) {
			continue;
		}
		if (u->getType().isWorker()) {
			if (u->isIdle()){
				workersIdle[*wIdleCount] = u;
				++wIdleCount;
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
		ScoutCard * c = orderQueue->GetHighestPriorityScoutCard();

		if (!c->onUse && c->priority != -1) {
			if (*wScoutCount > 0) {
				//if (c->unit->isIdle()) {
					if (c->unit->getPosition() != c->target) {
						c->unit->move(c->target);
					}
					else {
						orderQueue->RemoveCard(c, orderQueue->scoutCards, orderQueue->scoutCardsCount);
					}
				//}
				c->onUse = true;
			}
			else if (*wCristalCount > 0) {
				Unit u = GetClosestWorker(c->target, workersCristal, wCristalCount);
				u->stop();
				RemoveWorker(u, workersCristal, wCristalCount);
				SetWorker(u, workersScout, wScoutCount);
			}
		}
	}



	/*	if (*wScoutCount > 0)
	{
	/*SetWorkerToJob(c->unit, c);
	SetWorkerScout(c->unit);*/
	//Unit* u = GetClosestWorker(workersScout, wScoutsCount, c->tilePosition);
	/*			SetWorker(c->unit, workersScout, wScoutCount);
	}
	/*else if (*workersCristal > 0)
	{
	/*SetWorkerToJob(c->unit, c);
	SetWorkerScout(c->unit);*/
	/*Unit* u = GetClosestWorker(workersCristal, wCristalsCount, c->target);
	RemoveWorker(workersCristal, wCristalsCount, *u);
	SetWorker(c->unit, workersScout, wScoutsCount);

	}*/
	/*		c->onUse = true;
	}
	/*else
	{
	if (c->unit->getPosition() != c->target)
	{
	if (c->unit->isIdle()) {
	c->unit->move(c->target);
	//get unit enemy aux alentours
	// si unit alentours pas vide
	//si batiment alors enregistrer position enemy
	}
	}
	/*else
	{
	orderQueue->RemoveCard(c, orderQueue->scoutCards, orderQueue->scoutCardsCount);
	}*/
	//}
	//}
}

void WorkerManager::HandleWorkersBuilder() {
	for (int i = 0; i < *wBuilderCount; ++i) {
		if (workersBuilder[i]->isIdle()) {
			//Card * job = workersJob.at(workersBuilder[i]);

			BuildCard * c = orderQueue->GetHighestPriorityBuildCard();
			workersBuilder[i]->build(c->target, c->tilePosition);
			//workersBuilder[i]->build(job->target, job->pos);
		}
	}
}

void WorkerManager::SetWorkerToJob(Unit u, BaseCard * c){
	workersJob.insert(std::pair<Unit, BaseCard * >(u, c));
}

void WorkerManager::removeCard(Unit u, BaseCard * c){

}

/*Unit * WorkerManager::GetClosestWorkerIdle(PositionOrUnit pos){
double distance = 20000;
Unit * u;
int index = 0;

//Search for the nearest worker
for (int i = 0; i < wIdleCount; ++i){
if (workersIdle[i]->getDistance(pos) < distance){
distance = workersIdle[i]->getDistance(pos);
u = &workersIdle[i];
index = i;
}
}

//Reorganize the array
if (index != wIdleCount - 1 && wIdleCount > 1){
for (int i = index; i < wIdleCount; ++i){
workersIdle[i] = workersIdle[i + 1];
}
}
--wIdleCount;

return u;
}

Unit WorkerManager::GetClosestWorkerCristal(PositionOrUnit pos){
double distance = 20000;
Unit u;
int index = 0;

//Search for the nearest worker
for (int i = 0; i < wCristalsCount; ++i){
workersCristal[i]->stop();
if (workersCristal[i]->getDistance(pos) < distance){
distance = workersCristal[i]->getDistance(pos);
u = workersCristal[i];
index = i;
}
}

//Reorganize the array
for (int i = index; i < wCristalsCount; ++i){
workersCristal[i] = Unit();
workersCristal[i] = workersCristal[i + 1];
}

--wCristalsCount;
return u;
}

Unit WorkerManager::GetClosestWorkerBuilder(PositionOrUnit pos){
double distance = 20000;
Unit u;
int index = 0;

//Search for the nearest worker
for (int i = 0; i < wBuildersCount; ++i){
if (workersBuilder[i]->getDistance(pos) < distance){
distance = workersBuilder[i]->getDistance(pos);
u = workersBuilder[i];
index = i;
}
}

//Reorganize the array
if (index != wBuildersCount - 1){
for (int i = index; i < wBuildersCount; ++i){
workersBuilder[i] = workersBuilder[i + 1];
}
}
--wBuildersCount;

return u;
}

Unit * WorkerManager::GetClosestWorkerGas(PositionOrUnit pos){
double distance = 20000;
Unit * u;
int index = 0;

//Search for the nearest worker
for (int i = 0; i < wGasCount; ++i){
if (workersGas[i]->getDistance(pos) < distance){
distance = workersGas[i]->getDistance(pos);
u = &workersGas[i];
index = i;
}
}

//Reorganize the array
if (index != wGasCount - 1){
for (int i = index; i < wGasCount; ++i){
workersGas[i] = workersGas[i + 1];
}
}
--wGasCount;

return u;
}

Unit WorkerManager::GetClosestWorkerScout(PositionOrUnit pos){
double distance = 20000;
Unit u;
int index = 0;

//Search for the nearest worker
for (int i = 0; i < wScoutsCount; ++i){
if (workersScout[i]->getDistance(pos) < distance){
distance = workersScout[i]->getDistance(pos);
u = workersScout[i];
index = i;
}
}

//Reorganize the array
if (index != wScoutsCount - 1){
for (int i = index; i < wScoutsCount; ++i){
workersScout[i] = workersScout[i + 1];
}
}
--wScoutsCount;

return u;
}*/

/*void WorkerManager::SetWorkerCristal(Unit u){
workersCristal[wCristalsCount] = u;
++wCristalsCount;
}

void WorkerManager::SetWorkerBuilder(Unit u){
workersBuilder[wBuildersCount] = u;
++wBuildersCount;
}

void WorkerManager::SetWorkerGas(Unit u){
workersGas[wGasCount] = u;
++wGasCount;
}

void WorkerManager::SetWorkerScout(Unit u){
workersScout[wScoutsCount] = u;
++wScoutsCount;
}*/