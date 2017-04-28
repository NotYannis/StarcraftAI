#include "OrderQueue.h"

OrderQueue::OrderQueue() {
	list = new Card[100]; cardCount = 1;
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
Card OrderQueue::getHighestPriority(CardType type){
	Card high;
	for (int i = 0; i < cardCount; ++i){
		if (high < list[i] && list[i].type == type){
			high = list[i];
		}
	}

	return high;
}*/

//NEW
//Return the card with the highest priority
Card * OrderQueue::getHighestPriority(CardType type){
	Card * high;
	for (int i = 0; i < cardCount; ++i){
		if (high < &list[i] && list[i].type == type){
			high = &list[i];
		}
	}

	return high;
}

//Add a card to the queue
void OrderQueue::addCard(Card card){
	list[cardCount] = card;
	//cardCount += 1;
}

Card OrderQueue::GetBuildingCard(UnitType building){
	for (int i = 0; i < cardCount; ++i){
		if (list[i].target == building){
			return list[i];
		}
	}
	return Card();
}

//Remove a card from the queue
void OrderQueue::removeCard(Card card){
	bool found = false;

	for (int i = 0; i < cardCount; ++i){
		if (!found){
			if (card == list[i]){
				found = true;
			}
		}
		else if (i < cardCount - 1){
			list[i] == list[i + 1];
		}
	}

	--cardCount;
}
