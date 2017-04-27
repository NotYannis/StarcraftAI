#pragma once

#include "Common.h"

//Structure used to give an order to a unit.
struct Card{
	Unit target; //Unit to build
	int priority = 0;		//Priority of the card
	int quantity = 0;		//Quantity of ressources to gather
	bool isGas = false;
	bool blocking;		//Is it a blocking order or not ?
	BWAPI::Unit unit;	//The unit used for the task
	Position m_position;

	Card(){	}

	//Constructor for gathering ressources
	Card(int p, int q, bool g, bool b, BWAPI::Unit u){
		priority = p;
		quantity = q / 8;
		isGas = g;
		blocking = b;
		unit = u;
	}

	//Constructor for creating something (building, unit, research)
	Card(BWAPI::Unit t, int p, bool b, BWAPI::Unit u){
		target = t;
		priority = p;
		blocking = b;
		unit = u;
	}

	Card(Position position, int p, bool b, BWAPI::Unit u){
		m_position = position;
		priority = p;
		blocking = b;
		unit = u;
	}

	bool operator<(const Card &x) const
	{
		return priority < x.priority;
	}

	bool operator==(const Card &c) const
	{
		return target == c.target && priority == c.priority && quantity == c.quantity
			&& isGas == c.isGas && blocking == c.blocking && unit == c.unit;
	}
};

//This class is used to store all the cards in a queue
//The queue is ordered by card's priority (lowest on front)
class OrderQueue{
	public :
		Card * list;
		int cardCount;

		OrderQueue();
		~OrderQueue();
		static OrderQueue & Instance();

		Card * getHighestPriority(); //Return the highest priority card

		void addCard(Card card); //Add a card to the queue
		void removeCard(Card card); //Remove a card from the queue
};