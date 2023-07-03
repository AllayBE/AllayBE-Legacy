#pragma once

#include "PacketsHandlerManager.h"
#include <cstdint>
#include <DS_Map.h>
#include <misc/BitStreamHelper.h>
#include <network/minecraft/packets/GamePacket.h>
#include <network/minecraft/packets/LoginPacket.h>
#include <network/minecraft/packets/MinecraftPacket.h>
#include <network/minecraft/packets/NetworkSettingsPacket.h>
#include <network/minecraft/packets/PacketDefinitions.h>
#include <network/minecraft/packets/PlayStatusPacket.h>
#include <network/minecraft/packets/RequestNetworkSettingsPacket.h>
#include <network/minecraft/packets/ResourcePacksInfoPacket.h>
#include <player/Player.h>

using namespace RakNet;

typedef DataStructures::Map<uint32_t, MinecraftPacket *> PacketList_t;

class PacketManager
{
private:
	PacketList_t list;
	PacketsHandlerManager *packetsHandlerManager;

public:
	PacketManager();

	bool Add(uint32_t id, MinecraftPacket *packet);
	bool Remove(uint32_t id);
	MinecraftPacket *Get(uint32_t id);
	PacketList_t GetAll();
	PacketsHandlerManager *GetPacketsHandlerManager();
	void HandleGameStreams(StreamList_t streams, Player *player);
};