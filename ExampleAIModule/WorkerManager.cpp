#include "WorkerManager.h"
#include "StrategyManager.h"


WorkerManager::WorkerManager()
{
	workersGas = new Unit[20]; wGasCount = 0;
	workersCristal = new Unit[60]; wCristalsCount = 0;
	workersBuilder = new Unit[10]; wBuildersCount = 0;
	workersIdle = new Unit[50]; wIdleCount = 0;
	workersScout = new Unit[10]; wScoutsCount = 0;
}


WorkerManager::~WorkerManager(){
	delete[] workersGas;
	delete[] workersCristal;
	delete[] workersBuilder;
	delete[] workersIdle;
	delete[] workersScout;
}

WorkerManager & WorkerManager::Instance()
{
	static WorkerManager instance;
	return instance;
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

void WorkerManager::HandleWorkerScout(){
	if (OrderQueue::Instance().cardCount > 0) {
		if (OrderQueue::Instance().scoutCardCount > 0) {
			Card * c = OrderQueue::Instance().getHighestPriority(scout);
			if (!c->blocking && c->priority != -1) {
				if (wScoutsCount > 0)
				{
					Unit u = GetClosestWorkerScout(c->m_position);
					c->unit = u;
					SetWorkerToJob(u, c);
					SetWorkerScout(u);
				}
				else
				{
					if (workersCristal > 0) {
						Unit u = GetClosestWorkerCristal(c->m_position);
						c->unit = u;
						SetWorkerToJob(u, c);
						SetWorkerScout(u);
					}
				}
				c->blocking = true;
			}
			else{
				if (c->unit->getPosition() != c->m_position) {
					c->unit->move(c->m_position);
					//Unit unitsetgdr = c->unit->getClosestUnit(IsEnemy);//getUnitsInRadius(/*c->unit->getType().sightRange(), IsEnemy*/20);
					//Broodwar << unitsetgdr << std::endl;
					/*if (!c->unit->getUnitsInRadius(c->unit->getType().sightRange(), IsEnemy).empty()) {
						Common::Instance().enemyposition = c->unit->getPosition();
						OrderQueue::Instance().removeCard(*c);
					}*/
				}
				else
				{
					OrderQueue::Instance().removeCard(*c);
				}
			}
		}
	}
}


	/*for (int i = 0; i < wScoutsCount; ++i){
		if (workersScout[i]->isIdle()){
			Card job = workersJob.at(workersScout[i]);
			if (workersScout[i]->getPosition() != job.m_position) {
				workersScout[i]->move(job.m_position);
			}
			else {
				//workersJob.(workersScout[i]);
			}
			Broodwar << job.m_position.x << " " << job.m_position.y << std::endl;
			Broodwar << Broodwar->self()->getStartLocation().x << " " << Broodwar->self()->getStartLocation().y << std::endl;
		}
	}*/
//}


void WorkerManager::HandleWorkersBuilder(){
	for (int i = 0; i < wBuildersCount; ++i){
		if (workersBuilder[i]->isIdle()){
			Broodwar << workersJob.at(workersBuilder[i]).target << std::endl;
			Card job = workersJob.at(workersBuilder[i]);
			workersBuilder[i]->build(job.target, job.pos);
		}
	}
}

void WorkerManager::SetWorkerToJob(Unit u, Card * c){
	workersJob.insert(std::pair<Unit, Card>(u, *c));
}

void WorkerManager::removeCard(Unit u, Card * c){

}