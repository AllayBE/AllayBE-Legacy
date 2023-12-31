#pragma once

#include "RakNetOfflineMessage.h"
#include <BitStream.h>
#include <console/Logger.h>
#include <managers/PacketManager.h>
#include <managers/PlayerManager.h>
#include <MessageIdentifiers.h>
#include <network/minecraft/MinecraftVersionDefinitions.h>
#include <network/minecraft/packets/GamePacket.h>
#include <network/minecraft/packets/MinecraftPacket.h>
#include <network/minecraft/packets/PacketDefinitions.h>
#include <RakPeerInterface.h>

using namespace RakNet;

class RakNetInterface
{
protected:
	RakPeerInterface *peer;
	SocketDescriptor *descriptor;
	RakNetOfflineMessage *offlineMessage;
	bool initialized;
	bool running;
	Logger *logger;
	PacketManager *packetManager;
	PlayerManager *playerManager;

public:
	RakNetInterface(SocketDescriptor *descriptor, RakNetOfflineMessage *offlineMessage);

	bool isInitialized();
	bool isRunning();

	bool Initialize();
	bool Start();

	void SetMotd(char *value);
	void SetSecondMotd(char *value);

	PlayerManager *GetPlayerManager();
	PacketManager *GetPacketManager();

	void UpdatePong();
	void Handle();
	void Shutdown();

	uint64_t Generate64BitUnqiueNumber();
	uint32_t Generate32BitUnqiueNumber();
};