#pragma once

#include <cstdint>
#include <DS_Map.h>
#include <misc/BitStreamHelper.h>
#include <network/minecraft/packets/GamePacket.h>
#include <network/minecraft/packets/MinecraftPacket.h>
#include <network/minecraft/packets/PacketDefinitions.h>
#include <network/minecraft/packets/RequestNetworkSettingsPacket.h>
#include <player/Player.h>

using namespace RakNet;

#ifndef PACKET_MANAGER_
#define PACKET_MANAGER_

typedef DataStructures::Map<uint32_t, MinecraftPacket *> PacketList_t;

class PacketManager
{
private:
	PacketList_t list;

public:
	PacketManager();

	bool Add(uint32_t id, MinecraftPacket *packet);
	bool Remove(uint32_t id);
	MinecraftPacket *Get(uint32_t id);
	PacketList_t GetAll();
	void HandleGameStreams(StreamsList_t streams, Player *player);
};

#endif