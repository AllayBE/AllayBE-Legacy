#pragma once

#include <cstdint>

class PlayStatusTypes
{
public:
	static int32_t LoginSuccess()
	{
		return 0;
	}

	static int32_t LoginFailedClient()
	{
		return 1;
	}

	static int32_t LoginFailedServer()
	{
		return 2;
	}

	static int32_t PlayerSpawn()
	{
		return 3;
	}

	static int32_t LoginFailedInvalidTenant()
	{
		return 4;
	}

	static int32_t LoginFailedVanillaEdu()
	{
		return 5;
	}

	static int32_t LoginFailedEduVanilla()
	{
		return 6;
	}

	static int32_t LoginFailedServerFull()
	{
		return 7;
	}

	static int32_t LoginFailedEditorVanilla()
	{
		return 8;
	}

	static int32_t LoginFailedVanillaEditor()
	{
		return 9;
	}
};