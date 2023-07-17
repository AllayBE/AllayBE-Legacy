#pragma once

#include <cstdint>

class PermissionLevels
{
public:
	static uint8_t Visitor()
	{
		return 0;
	}

	static uint8_t Member()
	{
		return 1;
	}

	static uint8_t Operator()
	{
		return 2;
	}

	static uint8_t Custom()
	{
		return 3;
	}
};