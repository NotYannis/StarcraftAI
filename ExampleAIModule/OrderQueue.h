#pragma once

#include "Common.h"

enum CardType{ build, scout};
//Structure used to give an order to a unit.
struct Card{
	CardType type;
	UnitType target; //Unit to build
	int priority = -1;		//Priority of the card
	TilePosition pos = TilePosition(0, 0);		//Quantity of ressources to gather
	Position m_position;
	bool blocking;		//Is it a blocking order or not ?
	BWAPI::Unit unit;	//The unit used for the task

	Card(){	}

	///<summary>Card used to give a creation order (building or unit)</summary>
	///<param name="t">Type of unit to build</param>
	///<param name="p">Priority of the order</param>
	///<param name="po">Position of the building</param>
	///<param name="b">Is it a blocking order</param>
	///<param name="u">The unit used for the order</param>
	Card(BWAPI::UnitType t, int p, TilePosition po, bool b){
		type = build;
		target = t;
		priority = p;
		pos = po;
		blocking = b;
	}

	Card(Position position, int p, bool b){
		type = scout;
		m_position = position;
		priority = p;
		blocking = b;
	}

	bool operator<(const Card &x) const
	{
		return priority < x.priority;
	}

	bool operator==(const Card &c) const
	{
		return type == c.type &&  target == c.target && priority == c.priority
			&& pos == c.pos && blocking == c.blocking && unit == c.unit;
	}
};

//This class is used to store all the cards in a queue
//The queue is ordered by card's priority (lowest on front)
class OrderQueue{
public:
	Card * list;
	int scoutCardCount;
	int buildCardCount;
	int highestPriority;

	OrderQueue();
	~OrderQueue();
	static OrderQueue & Instance();

	Card * getHighestPriority(CardType type); //Return the highest priority card
	Card * getSecondHighestPriority(CardType type); //Return the second highest priority card


	void addCard(Card card); //Add a card to the queue
	Card * GetBuildingCard(UnitType building);
	void removeCard(Card * card); //Remove a card from the queue
};
