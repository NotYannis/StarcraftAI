#pragma once

#include "Common.h"

class StrategyManager
{
public:
	Unit cargo;
	Card * workingCards;

	int workingCardsCount;

	StrategyManager();
	~StrategyManager();

	static StrategyManager & Instance();

	void Start();
	void Update();
	void cardDone(Card * c);
};