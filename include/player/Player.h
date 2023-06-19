#pragma once

#include <RakNetTypes.h>

using namespace RakNet;

#ifndef PLAYER_
#define PLAYER_

class Player
{
protected:
	SystemAddress address;

public:
	Player(SystemAddress address);

	SystemAddress GetAddress();
};

#endif
