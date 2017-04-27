#include "StrategyManager.h"
#include "OrderQueue.h"
#include "MapGrid.h"

#include <string>

StrategyManager::StrategyManager()
{
	for (auto &u : Broodwar->self()->getUnits()){
		if (u->getType().isResourceDepot())
			cargo = u;
		}
}


StrategyManager::~StrategyManager()
{
}

StrategyManager & StrategyManager::Instance(){
	static StrategyManager instance;
	return instance;
}



void StrategyManager::Start(){
	for (auto & u : Broodwar->self()->getUnits()){
		if (u->getType().isWorker()){
			WorkerManager::Instance().SetWorkerCristal(u);
		}
	}
	MapGrid::Instance().CreateMapGrid();
}

void StrategyManager::Update(){

	WorkerManager::Instance().HandleWorkersCristal();
	
	/*for (auto &u : Broodwar->self()->getUnits())
	{
		if (u->getType() == UnitTypes::Protoss_Nexus)
		{
			UnitType workerType = u->getType().getRace().getWorker();

			Card *card = new Card(workerType, 5, true);

			OrderQueue::Instance().addCard(*card);

		}

		Unit workerBuilder = u->getClosestUnit(GetType == workerType.whatBuilds().first &&
			(IsIdle || IsGatheringMinerals) &&
			IsOwned);
		
		


		for (int i = 0; i < 100; ++i)
		{
			workerBuilder->train(OrderQueue::Instance().getHighestPriority()->target);
		}
	}*/


	for (auto & u : Broodwar->self()->getUnits()){
		if (u->getType().isResourceDepot()) // A resource depot is a Command Center, Nexus, or Hatchery
		{

			// Order the depot to construct more workers! But only when it is idle.
			if (u->isIdle() && !u->train(u->getType().getRace().getWorker()))
			{
				// If that fails, draw the error at the location so that you can visibly see what went wrong!
				// However, drawing the error once will only appear for a single frame
				// so create an event that keeps it on the screen for some frames
				Position pos = u->getPosition();
				Error lastErr = Broodwar->getLastError();
				Broodwar->registerEvent([pos, lastErr](Game*){ Broodwar->drawTextMap(pos, "%c%s", Text::White, lastErr.c_str()); },   // action
					nullptr,    // condition
					Broodwar->getLatencyFrames());  // frames to run

				// Retrieve the supply provider type in the case that we have run out of supplies
				UnitType supplyProviderType = u->getType().getRace().getSupplyProvider();
				static int lastChecked = 0;

				// If we are supply blocked and haven't tried constructing more recently
				if (lastErr == Errors::Insufficient_Supply &&
					lastChecked + 400 < Broodwar->getFrameCount() &&
					Broodwar->self()->incompleteUnitCount(supplyProviderType) == 0)
				{
					lastChecked = Broodwar->getFrameCount();
					Broodwar->sendText("Check supply block !");

					// Retrieve a unit that is capable of constructing the supply needed
					Unit supplyBuilder = u->getClosestUnit(GetType == supplyProviderType.whatBuilds().first &&
						(IsIdle || IsGatheringMinerals) &&
						IsOwned);
					// If a unit was found
					if (supplyBuilder)
					{
						if (supplyProviderType.isBuilding())
						{
							TilePosition targetBuildLocation = Broodwar->getBuildLocation(supplyProviderType, supplyBuilder->getTilePosition());
							if (targetBuildLocation)
							{
								// Register an event that draws the target build location
								Broodwar->registerEvent([targetBuildLocation, supplyProviderType](Game*)
								{
									Broodwar->drawBoxMap(Position(targetBuildLocation),
										Position(targetBuildLocation + supplyProviderType.tileSize()),
										Colors::Blue);
								},
									nullptr,  // condition
									supplyProviderType.buildTime() + 100);  // frames to run

								// Order the builder to construct the supply structure
								supplyBuilder->build(supplyProviderType, targetBuildLocation);
							}
						}
						else
						{
							// Train the supply provider (Overlord) if the provider is not a structure
							supplyBuilder->train(supplyProviderType);
						}
					} // closure: supplyBuilder is valid
					else{
						Broodwar->sendText("No worker found!");
					}
				} // closure: insufficient supply
			} // closure: failed to train idle unit
		}
		else if (u->getType().getRace().getWorker())
		{
			/*if (u->isIdle())
			{*/
				if (WorkerManager::Instance().wScoutsCount < 1) {
					WorkerManager::Instance().SetWorkerScout(u);
				}
				/*else if (WorkerManager::Instance().wScoutsCount < 1) {
					WorkerManager::Instance().SetWorkerBuilder(u);
				}*/
				//WorkerManager::Instance().HandleWorkerScout();
			//}
			WorkerManager::Instance().HandleWorkerScout();
			//WorkerManager::Instance().HandleWorkersBuilder(UnitTypes::Protoss_Pylon);
		}
	}
}