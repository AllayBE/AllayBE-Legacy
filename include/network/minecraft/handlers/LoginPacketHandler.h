#pragma once

#include "PacketHandler.h"
#include <network/minecraft/constants/PlayStatus.h>
#include <network/minecraft/packets/LoginPacket.h>

class LoginPacketHandler : public PacketHandler
{
public:
	virtual bool ProcessPacket(MinecraftPacket *normalPacket, Player *player) override;
};