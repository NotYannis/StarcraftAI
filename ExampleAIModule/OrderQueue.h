#pragma once

#include "Common.h"

//Base structure used to give any kind of order to a unit
struct BaseCard 
{
	int priority = -1;	//Priority of the card
	Unit unit;			//The unit affected to the task
	bool onUse = false;	//Has it be affected or not ?

	BaseCard(){}

	BaseCard(int _priority, Unit _unit) {
		priority = _priority;
		unit = _unit;
	}

	bool operator<(const BaseCard &c) const {
		return priority < c.priority;
	}

	bool operator==(const BaseCard &c) const {
		return priority == c.priority &&
			unit == c.unit &&
			onUse == c.onUse;
	}
};

//Structure used to give a building order to a unit
struct BuildCard : BaseCard
{
	UnitType target;			//Unit to build
	TilePosition tilePosition;	//TilePosition where we want to build

	BuildCard(){}

	///<summary>Structure used to give a building order to a unit</summary>
	BuildCard(int _priority, Unit _unit, UnitType _target, TilePosition _tilePosition) {
		priority = _priority;
		unit = _unit;
		target = _target;
		tilePosition = _tilePosition;
	}

	bool operator==(const BuildCard &c) const {
		return priority == c.priority &&
			unit == c.unit &&
			onUse == c.onUse &&
			target == c.target &&
			tilePosition == c.tilePosition;
	}
};

//Structure used to give a scouting order to a unit
struct ScoutCard : BaseCard
{
	Position target; //Position where we want to scout

	ScoutCard(){}

	///<summary>Structure used to give a scouting order to a unit</summary>
	ScoutCard(int _priority, Unit _unit, Position _target) {
		priority = _priority;
		unit = _unit;
		target = _target;
	}

	bool operator==(const ScoutCard &c) const {
		return priority == c.priority &&
			unit == c.unit &&
			onUse == c.onUse &&
			target == c.target;
	}
};

//This class is used to store all the cards lists, 
//The queue is ordered by card's priority (lowest on front)
class OrderQueue 
{
public:
	BuildCard * buildCards; int * buildCardsCount;
	ScoutCard * scoutCards; int * scoutCardsCount;

	int highestPriority;

	OrderQueue();
	~OrderQueue();

	static OrderQueue & Instance();
		
	ScoutCard * GetHighestPriorityScoutCard();	//Return the highest priority scout card
	BuildCard * GetHighestPriorityBuildCard();	//Return the highest priority building card

	BuildCard * GetSecondHighestPriorityBuildCard();	//Return the second highest priority card

	void AddCard(BaseCard card, BaseCard* cardList, int * cardCount);		//Add a card to the queue
	void RemoveCard(BaseCard* card, BaseCard* cardList, int * cardCount);	//Remove a card from the queue

	//Card * GetBuildingCard(UnitType building);
};
