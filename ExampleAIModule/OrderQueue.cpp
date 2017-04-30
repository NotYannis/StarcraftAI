#include "OrderQueue.h"

OrderQueue::OrderQueue() {
	buildCards = new CardBuild[100]; buildCardsCount = 0;
	scoutCards = new CardScout[100]; scoutCardsCount = 0;
	highestPriority = 0;
}
OrderQueue::~OrderQueue() {
	delete[] buildCards;
	delete[] scoutCards;
}

OrderQueue & OrderQueue::Instance() {
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

//NEW
//Return the card with the highest priority
Card * OrderQueue::GetHighestPriority(Card* cardList, int * cardCount) {
	Card * high = &Card();

	for (int i = 0; i < *cardCount - 1; ++i) {
		if (high < &cardList[i]) {
			high = &cardList[i];
		}
	}
	return high;
}

//Return the card with the highest priority
Card * OrderQueue::GetSecondHighestPriority(Card* cardList, int * cardCount) {
	Card * high = &Card();

	for (int i = 0; i < *cardCount - 1; ++i) {
		if (high->priority < highestPriority && high->priority < cardList[i].priority) {
			high = &cardList[i];
		}
	}

	return high;
}

//Add a card to the queue
void OrderQueue::AddCard(Card card, Card* cardList, int * cardCount) {
	cardList[*cardCount - 1] = card;
	*cardCount += 1;
}

/*Card * OrderQueue::GetBuildingCard(UnitType building){
	Card * c = &(Card());
	for (int i = 0; i < scoutCardCount + buildCardCount - 1; ++i){
		if (list[i].target == building){
			return &list[i];
		}
	}
	return c;
}*/

//Remove a card from the queue
void OrderQueue::RemoveCard(Card* card, Card * cardList, int * cardCount) {
	bool found = false;

	for (int i = 0; i < *cardCount - 1; ++i) {
		if (!found) {
			if (card == &cardList[i]) {
				found = true;
				cardList[i] = Card();
			}
		}
		if(found) {
			cardList[i] = cardList[i + 1];
		}
	}

	*cardCount -= 1;
}

CardBuild* OrderQueue::gethighestprioritybuildtest()
{
	CardBuild * high = &CardBuild();

	for (int i = 0; i < buildCardsCount - 1; ++i) {
		if (high < &buildCards[i]) {
			high = &buildCards[i];
		}
	}
	return high;
}
