#pragma once

#include <RakNetTypes.h>

using namespace RakNet;

#ifndef PLAYER_
#define PLAYER_

class Player
{
protected:
	SystemAddress address;
	bool compressionEnabled;

public:
	Player(SystemAddress address);

	void SetCompressionEnabled(bool value);

	bool IsCompressionEnabled();

	SystemAddress GetAddress();
};

#endif