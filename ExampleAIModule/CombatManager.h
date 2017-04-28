#pragma once
#include "Common.h"

class CombatManager
{
	Unitset squad;
	Position pos;
	Unitset enemiesInRange;
	Unit priorityTarget;
	
public:
	CombatManager(Unitset s);
	~CombatManager();
	Unitset UpdateEnemiesinRange();
	void Attack();
	void SetPriorityTarget();
	void UpdateCombatManager();
	void MoveSquadTo(Position pos);
};

