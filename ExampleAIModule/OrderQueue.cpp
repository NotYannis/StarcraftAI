#include "OrderQueue.h"

OrderQueue::OrderQueue() {
	list = new Card[100]; cardCount = 0;
	highestPriority = 0;
}
OrderQueue::~OrderQueue(){
	delete[] list;
}

OrderQueue & OrderQueue::Instance(){
	static OrderQueue orderQueue;
	return orderQueue;
}

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
}

//Return the card with the highest priority
Card * OrderQueue::getSecondHighestPriority(CardType type){
	Card * high = &Card();
	for (int i = 0; i < cardCount; ++i){
		if (high->priority < highestPriority && high->priority < list[i].priority && list[i].type == type){
			high = &list[i];
		}
	}

	return high;
}

//Add a card to the queue
void OrderQueue::addCard(Card card){
	list[cardCount] = card;
	++cardCount;
}

Card * OrderQueue::GetBuildingCard(UnitType building){
	Card * c = &(Card());
	for (int i = 0; i < cardCount; ++i){
		if (list[i].target == building){
			return &list[i];
		}
	}
	return c;
}

//Remove a card from the queue
void OrderQueue::removeCard(Card * card){
	bool found = false;

	for (int i = 0; i < cardCount; ++i){
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

	--cardCount;
}
