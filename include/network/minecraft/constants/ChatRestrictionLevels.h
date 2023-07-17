#pragma once

#include <cstdint>

class ChatRestrictionLevels
{
public:
	static uint8_t None()
	{
		return 0;
	}

	static uint8_t Dropped()
	{
		return 1;
	}

	static uint8_t Disabled()
	{
		return 2;
	}
};