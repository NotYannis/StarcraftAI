#include "OrderQueue.h"

OrderQueue::OrderQueue() {
	list = new Card[100]; scoutCardCount = 0; buildCardCount = 0;
	highestPriority = 0;
}
OrderQueue::~OrderQueue(){
	delete[] list;
}

OrderQueue & OrderQueue::Instance(){
	static OrderQueue orderQueue;
	return orderQueue;
}

/*
OLD
//Return the card with the highest priority
Card * OrderQueue::getHighestPriority(CardType type){
	Card * high = &Card();
	for (int i = 0; i < cardCount; ++i){
		if (high->priority < list[i].priority && list[i].type == type){
			high = &list[i];
		}
	}

	highestPriority = high->priority;

	return high;
}*/

//Return the card with the highest priority
Card * OrderQueue::getSecondHighestPriority(CardType type){
	Card * high = &Card();
	for (int i = 0; i < scoutCardCount + buildCardCount - 1; ++i){
		if (high->priority < highestPriority && high->priority < list[i].priority && list[i].type == type){
			high = &list[i];
		}
	}

	return high;
}

//NEW
//Return the card with the highest priority
Card * OrderQueue::getHighestPriority(CardType type){
	Card * high;
	for (int i = 0; i < scoutCardCount + buildCardCount - 1; ++i){
		if (high < &list[i] && list[i].type == type){
			high = &list[i];
		}
	}

	return high;
}

//Add a card to the queue
void OrderQueue::addCard(Card card){
	list[scoutCardCount + buildCardCount - 1] = card;
	if (card.type == scout) ++scoutCardCount;
	else ++buildCardCount;
}

Card * OrderQueue::GetBuildingCard(UnitType building){
	Card * c = &(Card());
	for (int i = 0; i < scoutCardCount + buildCardCount - 1; ++i){
		if (list[i].target == building){
			return &list[i];
		}
	}
	return c;
}

//Remove a card from the queue
void OrderQueue::removeCard(Card * card){
	bool found = false;

	for (int i = 0; i < scoutCardCount + buildCardCount - 1; ++i){
		if (!found){
			if (card == &list[i]){
				found = true;
				list[i] = Card();
			}
		}
		if(found){
			list[i] = list[i + 1];
		}
	}

	if (card->target == scout) --scoutCardCount;
	else --buildCardCount;
}
