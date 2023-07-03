#pragma once

#include "PacketHandler.h"
#include <network/minecraft/constants/PlayStatusTypes.h>
#include <network/minecraft/packets/LoginPacket.h>
#include <network/minecraft/packets/ResourcePacksInfoPacket.h>

class LoginPacketHandler : public PacketHandler
{
public:
	virtual bool ProcessPacket(MinecraftPacket *normalPacket, Player *player) override;
};