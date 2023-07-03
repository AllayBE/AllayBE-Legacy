#pragma once

#include <cstdint>

class PlayStatusTypes
{
public:
	static uint8_t LoginSuccess()
	{
		return 0;
	}

	static uint8_t LoginFailedClient()
	{
		return 1;
	}

	static uint8_t LoginFailedServer()
	{
		return 2;
	}

	static uint8_t PlayerSpawn()
	{
		return 3;
	}

	static uint8_t LoginFailedInvalidTenant()
	{
		return 4;
	}

	static uint8_t LoginFailedVanillaEdu()
	{
		return 5;
	}

	static uint8_t LoginFailedEduVanilla()
	{
		return 6;
	}

	static uint8_t LoginFailedServerFull()
	{
		return 7;
	}

	static uint8_t LoginFailedEditorVanilla()
	{
		return 8;
	}

	static uint8_t LoginFailedVanillaEditor()
	{
		return 9;
	}
};