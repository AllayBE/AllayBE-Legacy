#pragma once

#include <cstdint>

class GameModes
{
public:
	static int32_t Survival()
	{
		return 0;
	}

	static int32_t Creative()
	{
		return 1;
	}

	static int32_t Adventure()
	{
		return 2;
	}

	static int32_t SurvivalSpectator()
	{
		return 3;
	}

	static int32_t CreativeSpectator()
	{
		return 4;
	}

	static int32_t FallBack()
	{
		return 5;
	}

	static int32_t Spectator()
	{
		return 6;
	}
};