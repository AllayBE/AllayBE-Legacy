#pragma once

#include <cstdint>

class ResourcePackClientResponses
{
public:
	static uint8_t None()
	{
		return 0;
	}

	static uint8_t Refused()
	{
		return 1;
	}

	static uint8_t SendPacks()
	{
		return 2;
	}

	static uint8_t HaveAllPacks()
	{
		return 3;
	}

	static uint8_t Completed()
	{
		return 4;
	}
};