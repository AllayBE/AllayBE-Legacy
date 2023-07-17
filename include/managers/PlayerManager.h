#pragma once

#include <DS_Map.h>
#include <player/Player.h>
#include <RakNetTypes.h>
#include <string>

using namespace RakNet;

typedef DataStructures::Map<size_t, Player *> PlayerList_t;

class PlayerManager
{
protected:
	PlayerList_t list;

public:
	~PlayerManager();

	size_t HashAddress(SystemAddress address);
	bool Has(size_t hashedAddress);
	bool Add(SystemAddress address, RakPeerInterface *peer);
	bool Remove(size_t hashedAddress);
	Player *Get(size_t hashedAddress);
	PlayerList_t GetAll();
};