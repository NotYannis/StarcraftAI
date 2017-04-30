#include "WorkerManager.h"
#include "StrategyManager.h"


WorkerManager::WorkerManager()
{
	workersGas = new Unit[20]; wGasCount = 0;
	workersCristal = new Unit[60]; wCristalsCount = 0;
	workersBuilder = new Unit[10]; wBuildersCount = 0;
	workersIdle = new Unit[50]; wIdleCount = 0;
	workersScout = new Unit[10]; wScoutsCount = 0;
	orderQueue = &OrderQueue::Instance();
}


WorkerManager::~WorkerManager(){
	delete[] workersGas;
	delete[] workersCristal;
	delete[] workersBuilder;
	delete[] workersIdle;
	delete[] workersScout;
	delete orderQueue;
}

WorkerManager & WorkerManager::Instance()
{
	static WorkerManager instance;
	return instance;
}

///<summary>Get the closest worker in the given array from the given position</summary>
Unit * WorkerManager::GetClosestWorker(Unit* workersList, int workerCount, PositionOrUnit pos){
	double distance = 20000;
	Unit * u;
	int index = 0;

	//Search for the nearest worker 
	for (int i = 0; i < workerCount; ++i){
		if (workersList[i]->getDistance(pos) < distance){
			distance = workersList[i]->getDistance(pos);
			u = &workersList[i];
			index = i;
		}
	}

	return u;
}

///<summary>Remove the worker in the given array</summary>
void WorkerManager::RemoveWorker(Unit* workersList, int workerCount, Unit target){
	int found = false;

	//Search for the nearest worker 
	for (int i = 0; i < workerCount; ++i){
		if (workersList[i] == target){
			found = true;
		}
		if (found){
			workersList[i] = workersList[i + 1];
		}
	}

	--workerCount;
}

///<summary>Set a worker in the given array</summary>
void WorkerManager::SetWorker(Unit* workersList, int workerCount, Unit u){
	workersList[workerCount] = u;
	++workerCount;
}

Unit * WorkerManager::GetClosestWorkerIdle(PositionOrUnit pos){
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
}

void WorkerManager::SetWorkerIdle(Unit u){
	workersIdle[wIdleCount] = u;
	++wIdleCount;
}

void WorkerManager::SetWorkerCristal(Unit u){
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
}

void WorkerManager::HandleWorkersIdle(){
	for (auto &u : Broodwar->self()->getUnits()){
		if (!u->exists()){
			continue;
		}
		if (u->getType().isWorker()){
			if (u->isIdle()){
				workersIdle[wIdleCount] = u;
				++wIdleCount;
			}
		}
	}
}

void WorkerManager::HandleWorkersCristal(){
	for (int i = 0; i < wCristalsCount; ++i){
		if (workersCristal[i]->isIdle()) {
			if (workersCristal[i]->isCarryingMinerals()){
				workersCristal[i]->returnCargo();
			}
			else
			{
				workersCristal[i]->gather(workersCristal[i]->getClosestUnit(IsMineralField));
			}
		}
	}
}

void WorkerManager::HandleWorkersGas(){
	for (int i = 0; i < wGasCount; ++i){
		if (workersGas[i]->isCarryingGas()){
			workersGas[i]->returnCargo();
		}
		else if (!workersGas[i]->getPowerUp()){
			workersGas[i]->gather(workersGas[i]->getClosestUnit(IsRefinery));
		}
	}
}

void WorkerManager::HandleWorkerScout() {
	/*if (orderQueue->scoutCardsCount > 0) 
	{
		Card * c = orderQueue->GetHighestPriority(orderQueue->scoutCards, orderQueue->scoutCardsCount);
		if (!c->onUse && c->priority != -1) 
		{
			if (wScoutsCount > 0)
			{
				SetWorkerToJob(c->unit, c);
				SetWorkerScout(c->unit);
			}
			else
			{
				if (workersCristal > 0) 
				{
					SetWorkerToJob(c->unit, c);
					SetWorkerScout(c->unit);
				}
			}
			c->onUse = true;
		}
		else 
		{
			if (c->unit->getPosition() != c->tilePosition)
			{
				if (c->unit->isIdle()) {
					c->unit->move(c->tilePosition);
					//get unit enemy aux alentours
					// si unit alentours pas vide 
					//si batiment alors enregistrer position enemy
				}
			}
			else
			{
				orderQueue->RemoveCard(c, orderQueue->scoutCards, orderQueue->scoutCardsCount);
			}
		}
	}*/
}


	/*for (int i = 0; i < wScoutsCount; ++i){
		if (workersScout[i]->isIdle()){
<<<<<<< HEAD
			Card * job = workersJob.at(workersScout[i]);
			workersScout[i]->move(job->m_position);
=======
			Card job = workersJob.at(workersScout[i]);
			if (workersScout[i]->getPosition() != job.m_position) {
				workersScout[i]->move(job.m_position);
			}
			else {
				//workersJob.(workersScout[i]);
			}
			Broodwar << job.m_position.x << " " << job.m_position.y << std::endl;
			Broodwar << Broodwar->self()->getStartLocation().x << " " << Broodwar->self()->getStartLocation().y << std::endl;
>>>>>>> 9d96c26f2fa9d00df034bc301039f2a7bddea8b8
		}
	}*/
//}


void WorkerManager::HandleWorkersBuilder() {
	for (int i = 0; i < wBuildersCount; ++i) {
		if (workersBuilder[i]->isIdle()) {
			//Card * job = workersJob.at(workersBuilder[i]);

			CardBuild * c = orderQueue->gethighestprioritybuildtest();
			workersBuilder[i]->build(c->target, c->tilePosition);
			//workersBuilder[i]->build(job->target, job->pos);
		}
	}
}

void WorkerManager::SetWorkerToJob(Unit u, Card * c){
	workersJob.insert(std::pair<Unit, Card * >(u, c));
}

void WorkerManager::removeCard(Unit u, Card * c){

}