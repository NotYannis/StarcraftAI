#include "OrderQueue.h"

OrderQueue::OrderQueue() {
	list = new Card[100];
	cardCount = 0;
}
OrderQueue::~OrderQueue(){
	delete[] list;
}

OrderQueue & OrderQueue::Instance(){
	static OrderQueue orderQueue;
	return orderQueue;
}

//Return the card with the highest priority
Card * OrderQueue::getHighestPriority(){
	Card * high;
	for (int i = 0; i < cardCount; ++i){
		if (high < &list[i]){
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

//Remove a card from the queue
void OrderQueue::removeCard(Card card){
	bool found = false;

	for(int i = 0; i < cardCount; ++i){
		if (!found){
			if(card == list[i]){
				found = true;
			}
		}
		else if(i < cardCount - 1){
			list[i] == list[i + 1];
		}
	}

	--cardCount;
}
