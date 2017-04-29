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
	if (OrderQueue::Instance().buildCardCount > 0){
		/*Card * c = OrderQueue::Instance().getHighestPriority(build);
		
		if (!c->blocking && c->priority != -1 && Broodwar->self()->minerals() - ressourcesNeeded > c->target.mineralPrice()){
			ressourcesNeeded += c->target.mineralPrice();
			Unit u = WorkerManager::Instance().GetClosestWorkerCristal(Position(c->pos.x, c->pos.y));
			c->unit = u;
			c->blocking = true;
			WorkerManager::Instance().SetWorkerToJob(u, c);
			WorkerManager::Instance().SetWorkerBuilder(u);
		}*/
	}
}

void BuildingManager::OnBuildingCreate(Unit u){
	ressourcesNeeded -= u->getType().mineralPrice();
	Card * c = OrderQueue::Instance().GetBuildingCard(u->getType());

	if (c->priority != -1){
		Unit u2 = WorkerManager::Instance().GetClosestWorkerBuilder(c->unit);
		WorkerManager::Instance().SetWorkerCristal(c->unit);
		Card * c2 = OrderQueue::Instance().getSecondHighestPriority(build);
		c2->pos = Broodwar->getBuildLocation(UnitTypes::Protoss_Gateway, u->getTilePosition());
	}
}

void BuildingManager::OnBuildingComplete(Unit u){
	Card * c = OrderQueue::Instance().GetBuildingCard(u->getType());
	if (c->priority != -1){
		OrderQueue::Instance().removeCard(OrderQueue::Instance().GetBuildingCard(u->getType()));
		Card * c2 = OrderQueue::Instance().getSecondHighestPriority(build);
		c2->pos = Broodwar->getBuildLocation(UnitTypes::Protoss_Gateway, u->getTilePosition());
	}
}