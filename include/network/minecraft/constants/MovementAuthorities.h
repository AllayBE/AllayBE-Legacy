#pragma once

#include <cstdint>

class MovementAuthorities
{
public:
	static int32_t Client()
	{
		return 0;
	}

	static int32_t Server()
	{
		return 1;
	}

	static int32_t ServerWithRewind()
	{
		return 2;
	}
};