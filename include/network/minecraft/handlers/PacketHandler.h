#pragma once

#include <network/minecraft/packets/RequestNetworkSettingsPacket.h>
#include <player/Player.h>

class PacketHandler
{
public:
	virtual bool processPacket(MinecraftPacket *normalPacket, Player *player) = 0;
};