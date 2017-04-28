#include "WarManager.h"


WarManager::WarManager(int nzis)
{
	nbZealotInSquad = nzis;
	found = false;
	nbZealotReadyPerGateway = new std::vector<std::pair<Unit, int>>();
	squadsManager = new std::vector<CombatManager>();
	Gateways.getUnitsInRadius(9999, Filter::IsBuilding);
	for each (Unit u in Gateways)
	{
		if (u->getType() != UnitTypes::Protoss_Gateway)
		{
			Gateways.erase(u);
		}
	}
	std::pair<Unit, int> pair;
	if (Gateways.size() != 0)
	{
		for each (Unit u in Gateways)
		{
			pair.first = u;
			pair.second = 0;
			nbZealotReadyPerGateway->push_back(pair);
		}
	}
}


WarManager::~WarManager()
{
}

void WarManager::AddGateway(Unit u)
{
	if (u->getType() == UnitTypes::Protoss_Gateway)
	{
		std::pair<Unit, int> pair;
		Gateways.emplace(u);
		pair.first = u;
		pair.second = 0;
		nbZealotReadyPerGateway->push_back(pair);
	}
}

void WarManager::SendSquads()
{
	for each (std::pair<Unit, int> nbZealot in *nbZealotReadyPerGateway)
	{
		if (nbZealot.second >= nbZealotInSquad)
		{
			Unitset newSquad;
			newSquad.getUnitsInRadius(nbZealot.first->getType().sightRange(), Filter::CanMove && Filter::CanAttack);
			CombatManager* squad = new CombatManager(newSquad);
			squadsManager->push_back(*squad);
			squad->MoveSquadTo(enemyBase);
		}
	}
}

void WarManager::CheckZealots(Unit u)
{
	if (u->getType() == UnitTypes::Protoss_Zealot)
	{
		Unit gw;
		gw = u->getClosestUnit(Filter::IsBuilding, u->getType().sightRange());
		bool found = false;
		int cpt = 0;
		while (found == false || cpt < nbZealotReadyPerGateway->size())
		{
			if (nbZealotReadyPerGateway->at(cpt).first == gw)
			{
				++nbZealotReadyPerGateway->at(cpt).second;
				found = true;
			}
			++cpt;
		}
		if (found)
			SendSquads();
	}
}

void WarManager::Update(Unit u)
{
	AddGateway(u);
	CheckZealots(u);
}

void WarManager::Update()
{
	if (found)
	{
		for each (CombatManager squad in *squadsManager)
		{
			squad.UpdateCombatManager();
		}
	}
}

void WarManager::EnemyBaseFound(Position pos)
{
	enemyBase = pos;
	found = true;
}
