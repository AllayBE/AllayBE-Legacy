#pragma once

#include <BitStream.h>
#include <cstdint>
#include <stdexcept>
#include <exceptions/Exceptions.h>
#include "PacketDefinitions.h"
#include <misc/BitStreamHelper.h>

using namespace RakNet;

class MinecraftPacket
{
public:
	bool serialized;

public:
	MinecraftPacket();

	virtual uint32_t GetID() const = 0;

	void deserialize(BitStream *straem);
	void serialize(BitStream *straem);

	virtual void deserializeHeader(BitStream *stream) = 0;
	virtual void serializeHeader(BitStream *stream) = 0;

	virtual bool deserializeBody(BitStream *stream) = 0;
	virtual void serializeBody(BitStream *stream) = 0;
};