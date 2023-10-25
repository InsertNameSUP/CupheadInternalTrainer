#pragma once
#include "MemoryManipulation.h"
class PlayerHacks
{
public:
	PlayerHacks(MemoryManipulation m);
	PlayerHacks();
	bool isInfiniteHealthEnabled;
	bool isSmallPlayerEnabled;
	void InfiniteHealth();
	void SmallPlayer();
};

