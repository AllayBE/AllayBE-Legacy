#pragma once

#include <RakPeerInterface.h>
#include "RakNetOfflineMessage.h"
#include <network/minecraft/MinecraftVersionDefinitions.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <network/minecraft/packets/PacketDefinitions.h>
#include <player/Player.h>
#include <DS_Map.h>
#include <cstdint>
#include <string>

using namespace RakNet;

typedef DataStructures::Map<size_t, Player *> PlayerList_t;

#ifndef _RAKNET_INTERFACE
#define _RAKNET_INTERFACE

class RakNetInterface
{
protected:
	RakPeerInterface *peer;
	RakNetOfflineMessage *offlineMessage;
	SocketDescriptor *descriptor;
	bool initialized;
	bool running;
	PlayerList_t playerList;

public:
	RakNetInterface(SocketDescriptor *descriptor, RakNetOfflineMessage *offlineMessage);

	bool isInitialized();
	bool isRunning();

	bool Initialize();
	bool Start();
	void SetMotd(unsigned char *value);
	void SetSecondMotd(unsigned char *value);
	PlayerList_t GetPlayerList();
	void UpdatePong();
	void Handle();
	void FreeMemory();
	void Shutdown();

	uint64_t Generate64BitUnqiueNumber();
	uint32_t Generate32BitUnqiueNumber();
};

#endif