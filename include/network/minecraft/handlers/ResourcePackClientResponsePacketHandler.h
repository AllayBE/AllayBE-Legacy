#pragma once

#include "PacketHandler.h"
#include <network/minecraft/constants/ChatRestrictionLevels.h>
#include <network/minecraft/constants/Difficulties.h>
#include <network/minecraft/constants/Dimensions.h>
#include <network/minecraft/constants/GameModes.h>
#include <network/minecraft/constants/Generators.h>
#include <network/minecraft/constants/MovementAuthorities.h>
#include <network/minecraft/constants/PermissionLevels.h>
#include <network/minecraft/constants/PlayStatusTypes.h>
#include <network/minecraft/constants/ResourcePackClientResponses.h>
#include <network/minecraft/constants/XboxLiveBroadcastModes.h>
#include <network/minecraft/packets/BiomeDefinitionListPacket.h>
#include <network/minecraft/packets/CreativeContentPacket.h>
#include <network/minecraft/packets/ResourcePackStackPacket.h>
#include <network/minecraft/packets/StartGamePacket.h>
#include <ServerDefinitions.h>

class ResourcePackClientResponsePacketHandler : public PacketHandler
{
public:
	virtual bool ProcessPacket(MinecraftPacket *normalPacket, Player *player) override;
};