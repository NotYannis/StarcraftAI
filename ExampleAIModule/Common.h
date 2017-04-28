#pragma once

#include <BWAPI.h>
#include <map>

using namespace BWAPI;
using namespace Filter;

class Common
{
public:

	Position enemyposition;

	static Common & Instance();

	Common();
	~Common();
};

