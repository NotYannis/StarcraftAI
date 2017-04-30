#pragma once

#include "Common.h"

//Base structure used to give any kind of order to a unit
struct Card 
{
	int priority = -1;	//Priority of the card
	Unit unit;			//The unit affected to the task
	TilePosition tilePosition;	//Position where we want to build or scout
	bool onUse = false;	//Has it be affected or not ?

	Card(){}

	Card(int _priority, Unit _unit, TilePosition _tilePosition) {
		priority = _priority;
		unit = _unit;
		tilePosition = _tilePosition;
	}

	bool operator<(const Card &c) const {
		return priority < c.priority;
	}

	bool operator==(const Card &c) const {
		return priority == c.priority &&
			unit == c.unit &&
			tilePosition == c.tilePosition &&
			onUse == c.onUse;
	}
};

//Structure used to give a building order to a unit
struct CardBuild : Card 
{
	UnitType target;			//Unit to build

	CardBuild(){}

	///<summary>Structure used to give a building order to a unit</summary>
	CardBuild(int _priority, Unit _unit, Position _position, UnitType _target) {
		target = _target;
	}

	bool operator==(const CardBuild &c) const {
		return priority == c.priority &&
			unit == c.unit &&
			tilePosition == c.tilePosition &&
			onUse == c.onUse &&
			target == c.target;
	}
};

//Structure used to give a scouting order to a unit
struct CardScout : Card 
{
	CardScout(){}

	///<summary>Structure used to give a scouting order to a unit</summary>
	CardScout(int _priority, Unit _unit, TilePosition _tilePosition) {
		priority = _priority;
		unit = _unit;
		tilePosition = _tilePosition;
	}

	bool operator==(const CardScout &c) const {
		return priority == c.priority &&
			unit == c.unit &&
			tilePosition == c.tilePosition &&
			onUse == c.onUse;
	}
};

//This class is used to store all the cards lists, 
//The queue is ordered by card's priority (lowest on front)
class OrderQueue 
{
public:
	CardBuild* buildCards; int buildCardsCount;
	CardScout* scoutCards; int scoutCardsCount;

	int highestPriority;

	OrderQueue();
	~OrderQueue();
	static OrderQueue & Instance();

	Card* GetHighestPriority(Card* cardList, int * cardCount);		//Return the highest priority card
	Card* GetSecondHighestPriority(Card* cardList, int * cardCount);	//Return the second highest priority card

	CardBuild* gethighestprioritybuildtest();

	//Card * GetBuildingCard(UnitType building);

	void AddCard(Card card, Card* cardList, int * cardCount);		//Add a card to the queue
	void RemoveCard(Card* card, Card* cardList, int * cardCount);	//Remove a card from the queue
};
