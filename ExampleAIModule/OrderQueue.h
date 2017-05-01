#pragma once

#include "Common.h"

//Base structure used to give any kind of order to a unit
struct Card 
{
	int priority = -1;	//Priority of the card
	bool onUse = false;	//Has it be affected or not ?

	Card(){}

	Card(int _priority) {
		priority = _priority;
	}

	bool operator==(const Card &c) const {
		return priority == c.priority &&
			onUse == c.onUse;
	}
};

//Structure used to give a building order to a unit
struct BuildCard : Card
{
	UnitType target;			//Unit to build
	TilePosition tilePosition;	//TilePosition where we want to build
	int mineralPrice;
	int gasPrice;

	BuildCard(){}

	///<summary>Structure used to give a building order to a unit</summary>
	BuildCard(int _priority, UnitType _target, TilePosition _tilePosition) {
		priority = _priority;
		target = _target;
		tilePosition = _tilePosition;
		mineralPrice = target.mineralPrice();
		gasPrice = target.gasPrice();
	}

	bool operator==(const BuildCard &c) const {
		return priority == c.priority &&
			onUse == c.onUse &&
			target == c.target &&
			tilePosition == c.tilePosition &&
			mineralPrice == c.mineralPrice &&
			gasPrice == c.gasPrice;
	}
};

//Structure used to give a scouting order to a unit
struct ScoutCard : Card
{
	Position target; //Position where we want to scout

	ScoutCard(){}

	///<summary>Structure used to give a scouting order to a unit</summary>
	ScoutCard(int _priority, Position _target) {
		priority = _priority;
		target = _target;
	}

	bool operator==(const ScoutCard &c) const {
		return priority == c.priority &&
			onUse == c.onUse &&
			target == c.target;
	}
};

//This class is used to store all the cards lists, 
//The queue is ordered by card's priority (lowest on front)
class OrderQueue 
{
public:
	BuildCard ** buildCards; int * buildCardsCount;
	ScoutCard ** scoutCards; int * scoutCardsCount;

	int highestPriority;

	OrderQueue();
	~OrderQueue();

	static OrderQueue & Instance();
		
	ScoutCard * GetHighestPriorityScoutCard(); //Return the highest priority scout card
	BuildCard * GetHighestPriorityBuildCard(); //Return the highest priority building card

	BuildCard * GetSecondHighestPriorityBuildCard(); //Return the second highest priority card

	void AddBuildCard(BuildCard * card); //Add a BuildCard to the buildCards queue
	void AddScoutCard(ScoutCard * card); //Add a ScoutCard to the scoutCards queue

	void RemoveBuildCard(BuildCard * card); //Remove a BuildCard from the buildCards queue
	void RemoveScoutCard(ScoutCard * card); //Remove a ScoutCard from the scoutCards queue

	//Card * GetBuildingCard(UnitType building);
};
