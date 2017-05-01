#include "OrderQueue.h"

OrderQueue::OrderQueue() {
	buildCards = new BuildCard*[100]; buildCardsCount = new int(0);
	scoutCards = new ScoutCard*[100]; scoutCardsCount = new int(0);
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
	ScoutCard * high = new ScoutCard();

	for (int i = 0; i < *scoutCardsCount - 1; ++i) {
		if (high->priority < scoutCards[i]->priority) {
			high = scoutCards[i];
		}
	}
	return high;
}

//Return the highest priority building card
BuildCard * OrderQueue::GetHighestPriorityBuildCard() {
	BuildCard * high =  new BuildCard();

	for (int i = 0; i < *buildCardsCount; ++i) {
		if (high->priority < buildCards[i]->priority) {
			high = buildCards[i];
		}
	}
	return high;
}

//Return the second highest priority card
BuildCard * OrderQueue::GetSecondHighestPriorityBuildCard() {
	BuildCard * high = new BuildCard();

	for (int i = 0; i < *buildCardsCount - 1; ++i) {
		if (high->priority < highestPriority && high->priority < buildCards[i]->priority) {
			high = buildCards[i];
		}
	}
	return high;
}

//Add a BuildCard to the buildCards queue
void OrderQueue::AddBuildCard(BuildCard * card) {
	buildCards[*buildCardsCount] = card;
	++*buildCardsCount;
}

//Add a ScoutCard to the scoutCards queue
void OrderQueue::AddScoutCard(ScoutCard * card) {
	scoutCards[*scoutCardsCount] = card;
	++*scoutCardsCount;
}

//Remove a BuildCard from the buildCards queue
void OrderQueue::RemoveBuildCard(BuildCard * card) {
	bool found = false;

	for (int i = 0; i < *buildCardsCount; ++i) {
		if (!found) {
			if (card == buildCards[i]) {
				found = true;
				buildCards[i] = new BuildCard();
			}
		}
		if(found) {
			buildCards[i] = buildCards[i + 1];
		}
	}

	--*buildCardsCount;
}

//Remove a ScoutCard from the scoutCards queue
void OrderQueue::RemoveScoutCard(ScoutCard * card) {
	bool found = false;

	for (int i = 0; i < *scoutCardsCount; ++i) {
		if (!found) {
			if (card == scoutCards[i]) {
				found = true;
				scoutCards[i] = new ScoutCard();
			}
		}
		if (found) {
			scoutCards[i] = scoutCards[i + 1];
		}
	}

	--*scoutCardsCount;
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
