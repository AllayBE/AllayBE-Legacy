#pragma once

#include <BitStream.h>
#include <cstdint>
#include <stdexcept>
#include <exceptions/Exceptions.h>
#include "PacketDefinitions.h"
#include <misc/BitStreamHelper.h>
#include <console/Logger.h>

using namespace RakNet;

#ifndef MINECRAFT_PACKET_
#define MINECRAFT_PACKET_

class MinecraftPacket
{
protected:
	Logger *logger;

public:
	bool serialized;

public:
	MinecraftPacket();

	virtual uint32_t GetID() const = 0;

	virtual void deserialize(BitStream *straem) = 0;
	virtual void serialize(BitStream *straem) = 0;

	virtual void deserializeHeader(BitStream *stream) = 0;
	virtual void serializeHeader(BitStream *stream) = 0;

	virtual void deserializeBody(BitStream *stream) = 0;
	virtual void serializeBody(BitStream *stream) = 0;
};

#endif