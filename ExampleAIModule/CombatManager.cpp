#include "CombatManager.h"


CombatManager::CombatManager(Unitset s)
{
	squad = s;
	pos = squad.getPosition();
	enemiesInRange = UpdateEnemiesinRange();
	if (enemiesInRange.size() != 0)
	{
		SetPriorityTarget();
		Attack();
	}
}


CombatManager::~CombatManager()
{
}

Unitset CombatManager::UpdateEnemiesinRange()
{
	int maxSightRange = 0;
	for each (Unit u in squad)
	{
		if (u->getType().sightRange() > maxSightRange)
		{
			maxSightRange = u->getType().sightRange();
		}
	}
	Unitset enemies = squad.getUnitsInRadius(maxSightRange, Filter::IsEnemy);
	return enemies;
}

void CombatManager::SetPriorityTarget()
{
	if (enemiesInRange.size() != 0)
	{
		int minDist = 10000;
		for each (Unit e in enemiesInRange)
		{
			if (e->getDistance(squad.getPosition()) < minDist && !e->getType().isBuilding() && !e->getType().isWorker())
			{
				minDist = e->getDistance(squad.getPosition());
				priorityTarget = e;
			}
		}
		if (minDist = 10000)
		{
			for each (Unit e in enemiesInRange)
			{
				if (e->getDistance(squad.getPosition()) < minDist)
				{
					minDist = e->getDistance(squad.getPosition());
					priorityTarget = e;
				}
			}
		}
	}
}

void CombatManager::Attack()
{
	if (enemiesInRange.size() != 0)
	{
		squad.attack(priorityTarget, false);
	}
}

void CombatManager::UpdateCombatManager()
{
	pos = squad.getPosition();
	enemiesInRange = UpdateEnemiesinRange();
	if (enemiesInRange.size() != 0)
	{
		SetPriorityTarget();
		Attack();
	}
}

void CombatManager::MoveSquadTo(Position pos)
{
	squad.move(pos);
}
