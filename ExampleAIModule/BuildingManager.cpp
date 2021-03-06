#include "BuildingManager.h"


BuildingManager::BuildingManager()
{
	ressourcesNeeded = 0;
	orderQueue = &OrderQueue::Instance();
}


BuildingManager::~BuildingManager()
{
	delete orderQueue;
}

BuildingManager & BuildingManager::Instance(){
	static BuildingManager buildingManager;
	return buildingManager;
}

void BuildingManager::GetNextCard(){
	//if (orderQueue->buildCardsCount > 0) {
		/*Card * c = OrderQueue::Instance().getHighestPriority(build);
		
		if (!c->blocking && c->priority != -1 && Broodwar->self()->minerals() - ressourcesNeeded > c->target.mineralPrice()){
			ressourcesNeeded += c->target.mineralPrice();
			Unit u = WorkerManager::Instance().GetClosestWorkerCristal(Position(c->pos.x, c->pos.y));
			c->unit = u;
			c->blocking = true;
			WorkerManager::Instance().SetWorkerToJob(u, c);
			WorkerManager::Instance().SetWorkerBuilder(u);
		}*/
	//}
}

void BuildingManager::OnBuildingCreate(Unit u){
	ressourcesNeeded -= u->getType().mineralPrice();
	BuildCard * c = orderQueue->GetHighestPriorityBuildCard();

	if (c->priority != -1){
		/*Unit u2 = WorkerManager::Instance().GetClosestWorkerBuilder(c->unit);
		WorkerManager::Instance().SetWorkerCristal(c->unit);
		//Card * c2 = OrderQueue::Instance().getSecondHighestPriority(build);

		Card * c2 = orderQueue->GetSecondHighestPriority(orderQueue->buildCards, &orderQueue->buildCardsCount);
		c2->tilePosition = Broodwar->getBuildLocation(UnitTypes::Protoss_Gateway, u->getTilePosition());*/
	}
}

void BuildingManager::OnBuildingComplete(Unit u){
	BuildCard * c = orderQueue->GetHighestPriorityBuildCard();

	if (c->priority != -1){
		//OrderQueue::Instance().removeCard(OrderQueue::Instance().GetBuildingCard(u->getType()));

		//orderQueue->RemoveCard(orderQueue->GetHighestPriority(orderQueue->buildCards, orderQueue->buildCardsCount)));

		//orderQueue->RemoveCard(c, *orderQueue->buildCards, orderQueue->buildCardsCount);

		//Card * c2 = OrderQueue::Instance().getSecondHighestPriority(build);

		BuildCard * c2 = orderQueue->GetSecondHighestPriorityBuildCard();

		c2->tilePosition = Broodwar->getBuildLocation(UnitTypes::Protoss_Gateway, u->getTilePosition());
	}
}