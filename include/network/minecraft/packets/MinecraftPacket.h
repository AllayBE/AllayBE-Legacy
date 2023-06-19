#pragma once

#include <BitStream.h>
#include <cstdint>
#include <stdexcept>
#include <exceptions/Exceptions.h>
#include "PacketDefinitions.h"
#include <misc/BitStreamHelper.h>

using namespace RakNet;

#ifndef MINECRAFT_PACKET_
#define MINECRAFT_PACKET_

class MinecraftPacket
{
public:
	static const uint32_t id;
	bool serialized;

public:
	MinecraftPacket();

	void deserialize(BitStream *straem);
	void serialize(BitStream *straem);

	void deserializeHeader(BitStream *stream);
	void serializeHeader(BitStream *stream);

	void deserializeBody(BitStream *stream);
	void serializeBody(BitStream *stream);
};

#endif