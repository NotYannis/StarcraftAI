#include "BuildingManager.h"


BuildingManager::BuildingManager()
{
	ressourcesNeeded = 0;
}


BuildingManager::~BuildingManager()
{
	Card = OrderQueue::Instance().getHighestPriority();
}
