#pragma once

#include "Common.h"
#include "OrderQueue.h"
#include <vector>

class WorkerManager
{
public:
	//OrderQueue* orderQueue;

	std::map <Unit, Card *> workersJob;

	Unit * workersGas;
	Unit * workersCristal;
	Unit * workersBuilder;
	Unit * workersIdle;
	Unit * workersScout;	

	int wGasCount;
	int wCristalsCount;
	int wBuildersCount;
	int wIdleCount;
	int wScoutsCount;

	Unit * GetClosestWorker(Unit* workersList, int workerCount, PositionOrUnit pos);
	void RemoveWorker(Unit* workersList, int workerCount, Unit target);
	void SetWorker(Unit* workersList, int workerCount, Unit u);

	Unit * GetClosestWorkerIdle(PositionOrUnit pos);
	Unit GetClosestWorkerCristal(PositionOrUnit pos);
	Unit GetClosestWorkerBuilder(PositionOrUnit pos);
	Unit * GetClosestWorkerGas(PositionOrUnit pos);
	Unit GetClosestWorkerScout(PositionOrUnit pos);

	void SetWorker(Unit u, Unit* workersType, int &workersTypeCount);

	void HandleWorkersCristal();
	void HandleWorkersGas();
	void HandleWorkerScout();
	void HandleWorkersBuilder();
	void HandleWorkersIdle();

	void SetWorkerToJob(Unit u, Card * c);
	void removeCard(Unit u, Card * c);

	WorkerManager();
	~WorkerManager();

	static WorkerManager & Instance();
};

