#pragma once

#include <network/minecraft/constants/CompressionAlgorithmTypes.h>
#include <network/minecraft/constants/CompressionThresholdTypes.h>
#include <network/minecraft/MinecraftVersionDefinitions.h>
#include <network/minecraft/packets/NetworkSettingsPacket.h>
#include <network/minecraft/packets/RequestNetworkSettingsPacket.h>
#include <player/Player.h>

class PacketHandler
{
public:
	virtual bool ProcessPacket(MinecraftPacket *normalPacket, Player *player) = 0;
};