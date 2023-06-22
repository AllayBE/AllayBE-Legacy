#pragma once

#include "PacketHandler.h"

class RequestNetworkSettingsPacketHandler : public PacketHandler
{
public:
	virtual bool processPacket(MinecraftPacket *normalPacket, Player *player) override;
};