#pragma once

#include <cstdint>

class CompressionThresholdTypes
{
public:
	static uint16_t None()
	{
		return 0;
	}

	static uint16_t All()
	{
		return 1;
	}
};