#pragma once

#include <cstdint>

class XboxLiveBroadcastModes
{
public:
	static uint32_t None()
	{
		return 0;
	}

	static uint32_t Invite()
	{
		return 1;
	}

	static uint32_t Friends()
	{
		return 2;
	}

	static uint32_t FriendsOfFriends()
	{
		return 3;
	}

	static uint32_t Public()
	{
		return 4;
	}
};