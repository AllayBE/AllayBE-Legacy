#pragma once

#include <network/minecraft/packets/GamePacket.h>
#include <network/minecraft/packets/PlayStatusPacket.h>
#include <RakPeerInterface.h>

using namespace RakNet;

class Player
{
protected:
	SystemAddress address;
	size_t hashedAddress;
	RakPeerInterface *peer;
	bool compressionEnabled;
	int32_t protocolVersion;

public:
	Player(SystemAddress address, size_t hashedAddress, RakPeerInterface *peer);

	void SetCompressionEnabled(bool value);
	void SetProtocolVersion(int32_t value);

	bool IsCompressionEnabled();

	SystemAddress GetAddress();
	size_t GetHashedAddress();
	int32_t GetProtocolVersion();
	void SendPlayStatus(uint8_t status, bool force = false);
	void SendPacket(MinecraftPacket *packet, bool force = false);
};