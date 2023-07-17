#pragma once

#include <DS_Map.h>
#include <network/minecraft/handlers/LoginPacketHandler.h>
#include <network/minecraft/handlers/PacketHandler.h>
#include <network/minecraft/handlers/RequestNetworkSettingsPacketHandler.h>
#include <network/minecraft/handlers/ResourcePackClientResponsePacketHandler.h>

using namespace RakNet;

typedef DataStructures::Map<uint32_t, PacketHandler *> PacketHandlerList_t;

class PacketsHandlerManager
{
protected:
	PacketHandlerList_t list;

public:
	PacketsHandlerManager();
	~PacketsHandlerManager();

	bool Add(uint32_t id, PacketHandler *handler);
	bool Remove(uint32_t id);
	PacketHandler *Get(uint32_t id);
	PacketHandlerList_t GetAll();
};