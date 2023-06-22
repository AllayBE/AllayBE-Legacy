#pragma once

#include <network/minecraft/packets/GamePacket.h>
#include <PacketPriority.h>
#include <RakNetTypes.h>
#include <RakPeerInterface.h>

using namespace RakNet;

class Player
{
protected:
	SystemAddress address;
	size_t hashedAddress;
	bool compressionEnabled;
	RakPeerInterface *peer;

public:
	Player(SystemAddress address, size_t hashedAddress, RakPeerInterface *peer);

	void SetCompressionEnabled(bool value);

	bool IsCompressionEnabled();

	SystemAddress GetAddress();
	size_t GetHashedAddress();
	void SendPacket(MinecraftPacket *packet, bool force = false);
};