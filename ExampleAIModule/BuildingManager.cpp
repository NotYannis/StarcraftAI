#include "BuildingManager.h"


BuildingManager::BuildingManager()
{
	ressourcesNeeded = 0;
}


BuildingManager::~BuildingManager()
{

}

BuildingManager & BuildingManager::Instance(){
	static BuildingManager buildingManager;
	return buildingManager;
}

void BuildingManager::GetNextCard(){
	if (OrderQueue::Instance().cardCount > 0){
		Card *c = OrderQueue::Instance().getHighestPriority(build);
		if (Broodwar->self()->minerals() - ressourcesNeeded > c->target.mineralPrice()){
			ressourcesNeeded += c->target.mineralPrice();
			Unit u = WorkerManager::Instance().GetClosestWorkerCristal(Position(c->pos.x, c->pos.y));
			c->unit = u;
			WorkerManager::Instance().SetWorkerToJob(u, *c);
			WorkerManager::Instance().SetWorkerBuilder(u);
		}
	}
}

void BuildingManager::OnBuildingCreate(UnitType ut){
	ressourcesNeeded -= ut.mineralPrice();
	Card c = OrderQueue::Instance().GetBuildingCard(ut);
	if (c.priority != -1){
		Unit u = WorkerManager::Instance().GetClosestWorkerBuilder(c.unit);
		WorkerManager::Instance().SetWorkerCristal(c.unit);
	}
}

void BuildingManager::OnBuildingComplete(UnitType ut){
	Card c = OrderQueue::Instance().GetBuildingCard(ut);
	if (c.priority != -1){
		OrderQueue::Instance().removeCard(OrderQueue::Instance().GetBuildingCard(ut));
	}
}