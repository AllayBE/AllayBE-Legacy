#pragma once

#include <cstdint>

class GameRuleTypes
{
public:
	static uint32_t Bool()
	{
		return 0;
	}

	static uint32_t Int()
	{
		return 1;
	}

	static uint32_t Float()
	{
		return 2;
	}
};