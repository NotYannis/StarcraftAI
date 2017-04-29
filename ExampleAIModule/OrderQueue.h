#pragma once

#include "Common.h"

//Structure used to give a building order to a unit
struct CardBuild{
	UnitType target;						//Unit to build
	int priority = -1;						//Priority of the card
	TilePosition position = TilePosition(0, 0);	//Position where we want the building to be built
	BWAPI::Unit unit;						//The unit affected to the task
	bool onUse = false;						//Has it be affected or not ?

	CardBuild(){ }

	///<summary>Structure used to give a building order to a unit</summary>
	CardBuild(BWAPI::UnitType _target, int _priority, TilePosition _position){
		target = _target;
		priority = _priority;
		position = _position;
	}

	bool operator<(const CardBuild &x) const
	{
		return priority < x.priority;
	}

	bool operator==(const CardBuild &c) const
	{
		return target == c.target && priority == c.priority
			&& position == c.position && onUse == c.onUse && unit == c.unit;
	}
};

//Structure used to give a scouting order to a unit
struct CardScout{
	int priority = -1;	//Priority of the card
	Position position;	//Position to scout
	BWAPI::Unit unit;	//The unit used for the task
	bool onUse = false;	//Has it be affected or not ?

	CardScout(){	}

	///<summary>Structure used to give a scouting order to a unit</summary>
	CardScout(Position _position, int _priority){
		position = _position;
		priority = _priority;
	}

	bool operator<(const CardScout &x) const
	{
		return priority < x.priority;
	}

	bool operator==(const CardScout &c) const
	{
		return priority == c.priority && position == c.position && onUse == c.onUse && unit == c.unit;
	}
};

//This class is used to store all the cards in a queue
//The queue is ordered by card's priority (lowest on front)
class OrderQueue{
public:
	CardBuild * listBuild;
	CardScout * listScout;
	int scoutCardCount;
	int buildCardCount;
	int highestPriority;

	OrderQueue();
	~OrderQueue();
	static OrderQueue & Instance();

	void getHighestPriority(CardBuild * card); //Return the highest priority card
	Card * getSecondHighestPriority(CardType type); //Return the second highest priority card


	void AddCard(CardScout card); //Add a card to the queue
	void AddCard(CardBuild card); //Add a card to the queue
	Card * GetBuildingCard(UnitType building);
	void removeCard(Card * card); //Remove a card from the queue
};
