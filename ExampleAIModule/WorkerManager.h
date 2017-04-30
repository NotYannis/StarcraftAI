#pragma once

#include "Common.h"
#include "OrderQueue.h"

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

	int wGasCount;
	int wCristalsCount;
	int wBuildersCount;
	int wIdleCount;
	int wScoutsCount;

	Unit * GetClosestWorkerIdle(PositionOrUnit pos);
	Unit GetClosestWorkerCristal(PositionOrUnit pos);
	Unit GetClosestWorkerBuilder(PositionOrUnit pos);
	Unit * GetClosestWorkerGas(PositionOrUnit pos);
	Unit GetClosestWorkerScout(PositionOrUnit pos);

	void SetWorkerIdle(Unit u);
	void SetWorkerCristal(Unit u);
	void SetWorkerBuilder(Unit u);
	void SetWorkerGas(Unit u);
	void SetWorkerScout(Unit u);

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

