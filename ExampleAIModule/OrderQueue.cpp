#include "OrderQueue.h"

OrderQueue::OrderQueue() {
	buildCards = new BuildCard[100]; buildCardsCount = new int(0);
	scoutCards = new ScoutCard[100]; scoutCardsCount = new int(0);
	highestPriority = 0;
}

OrderQueue::~OrderQueue() {
	delete[] buildCards; delete buildCardsCount;
	delete[] scoutCards; delete scoutCardsCount;
}

OrderQueue & OrderQueue::Instance() {
	static OrderQueue orderQueue;
	return orderQueue;
}

//Return the highest priority scout card
ScoutCard * OrderQueue::GetHighestPriorityScoutCard() {
	ScoutCard * high = &ScoutCard();

	for (int i = 0; i < *scoutCardsCount - 1; ++i) {
		if (high < &scoutCards[i]) {
			high = &scoutCards[i];
		}
	}
	return high;
}

//Return the highest priority building card
BuildCard * OrderQueue::GetHighestPriorityBuildCard() {
	BuildCard * high = &BuildCard();

	for (int i = 0; i < *buildCardsCount - 1; ++i) {
		if (high < &buildCards[i]) {
			high = &buildCards[i];
		}
	}
	return high;
}

//Return the second highest priority card
BuildCard * OrderQueue::GetSecondHighestPriorityBuildCard() {
	BuildCard * high = &BuildCard();

	for (int i = 0; i < *buildCardsCount - 1; ++i) {
		if (high->priority < highestPriority && high->priority < buildCards[i].priority) {
			high = &buildCards[i];
		}
	}
	return high;
}

//Add a card to the queue
void OrderQueue::AddCard(BaseCard card, BaseCard * cardList, int * cardCount) {
	cardList[*cardCount - 1] = card;
	++*cardCount;
}

//Remove a card from the queue
void OrderQueue::RemoveCard(BaseCard * card, BaseCard * cardList, int * cardCount) {
	bool found = false;

	for (int i = 0; i < *cardCount - 1; ++i) {
		if (!found) {
			if (card == &cardList[i]) {
				found = true;
				cardList[i] = BaseCard();
			}
		}
		if(found) {
			cardList[i] = cardList[i + 1];
		}
	}

	*cardCount -= 1;
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
