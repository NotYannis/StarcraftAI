#pragma once

#include "Common.h"
#include "OrderQueue.h"
#include <vector>

class WorkerManager
{
public:
	OrderQueue* orderQueue;

	std::map <Unit, BaseCard *> workersJob;

	Unit * workersGas;
	Unit * workersCristal;
	Unit * workersBuilder;
	Unit * workersIdle;
	Unit * workersScout;	

	int * wGasCount;
	int * wCristalsCount;
	int * wBuildersCount;
	int * wIdlesCount;
	int * wScoutsCount;

	WorkerManager();
	~WorkerManager();

	static WorkerManager & Instance();

	Unit * GetClosestWorker(PositionOrUnit pos, Unit * workersList, int * workersCount); //Get the closest worker in the given array from the given position
	void RemoveWorker(Unit u, Unit * workersList, int * workersCount);					 //Remove the worker in the given array
	void SetWorker(Unit u, Unit * workersList, int * workersCount);						 //Set a worker in the given array

	void HandleWorkersCristal();
	void HandleWorkersGas();
	void HandleWorkerScout();
	void HandleWorkersBuilder();
	void HandleWorkersIdle();

	void SetWorkerToJob(Unit u, BaseCard * c);
	void removeCard(Unit u, BaseCard * c);

	/*Unit * GetClosestWorkerIdle(PositionOrUnit pos);
	Unit GetClosestWorkerCristal(PositionOrUnit pos);
	Unit GetClosestWorkerBuilder(PositionOrUnit pos);
	Unit * GetClosestWorkerGas(PositionOrUnit pos);
	Unit GetClosestWorkerScout(PositionOrUnit pos);

	void WorkerManager::SetWorkerCristal(Unit u)
	void WorkerManager::SetWorkerBuilder(Unit u)
	void WorkerManager::SetWorkerGas(Unit u)
	void WorkerManager::SetWorkerScout(Unit u)*/

};

