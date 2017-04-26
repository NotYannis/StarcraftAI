#include "StrategyManager.h"

StrategyManager::StrategyManager()
{
	workingCards = new Card[100]; workingCardsCount = 0;
	for (auto &u : Broodwar->self()->getUnits()){
		if (u->getType().isResourceDepot()){
			cargo = u;
		}
	}
}


StrategyManager::~StrategyManager()
{
	delete[] workingCards;
}

StrategyManager & StrategyManager::Instance(){
	static StrategyManager instance;
	return instance;
}



void StrategyManager::Start(){
	for (auto & u : Broodwar->self()->getUnits()){
		if (u->getType().isWorker()){
			WorkerManager::Instance().SetWorkerCristal(u);
			Card crystalCard = Card(10, 100, false, false, u);
			OrderQueue::Instance().addCard(crystalCard);
			WorkerManager::Instance().SetWorkerToJob(u, &crystalCard);
			workingCards[workingCardsCount] = crystalCard; ++workingCardsCount;
		}
	}
}

void StrategyManager::Update(){
	WorkerManager::Instance().HandleWorkersCristal();
}

void StrategyManager::cardDone(Card * c){
	bool found = false;
	for (int i = 0; i < workingCardsCount; ++i){
		if(!found){
			if (workingCards[i] == *c){
				found = true;
			}
		}
		else if(i < workingCardsCount - 1){
			workingCards[i] = workingCards[i + 1];
		}
	}

	--workingCardsCount;
}