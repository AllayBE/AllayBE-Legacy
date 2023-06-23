#pragma once

#include "PacketHandler.h"

class RequestNetworkSettingsPacketHandler : public PacketHandler
{
public:
	virtual bool ProcessPacket(MinecraftPacket *normalPacket, Player *player) override;
};