#pragma once

#include "Common.h"
#include "OrderQueue.h"
#include <vector>

class WorkerManager
{
public:
	OrderQueue* orderQueue;

	std::map <Unit, Card *> workersJob;

	Unit * workersGas;
	Unit * workersCristal;
	Unit * workersBuilder;
	Unit * workersIdle;
	Unit * workersScout;	

	int * wGasCount;
	int * wCristalCount;
	int * wBuilderCount;
	int * wIdleCount;
	int * wScoutCount;

	WorkerManager();
	~WorkerManager();

	static WorkerManager & Instance();

	Unit GetClosestWorker(PositionOrUnit pos, Unit * workersList, int * workersCount);	//Get the closest worker in the given array from the given position
	void RemoveWorker(Unit u, Unit * workersList, int * workersCount);					//Remove the worker in the given array
	void AddWorker(Unit u, Unit * workersList, int * workersCount);						//Set a worker in the given array
	bool SearchWorker(Unit u, Unit * workersList, int * workersCount);					//Search a worker in the given array

	void HandleWorkersCristal();
	void HandleWorkersGas();
	void HandleWorkerScout();
	void HandleWorkersBuilder();
	void HandleWorkersIdle();

	void SetWorkerToJob(Unit u, Card * c);
	void removeCard(Unit u, Card * c);
};

