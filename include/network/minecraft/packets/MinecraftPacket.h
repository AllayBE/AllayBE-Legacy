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
	virtual uint32_t GetID() const = 0;

	void Deserialize(BitStream *straem);
	void Serialize(BitStream *straem);

	virtual void DeserializeHeader(BitStream *stream) = 0;
	virtual void SerializeHeader(BitStream *stream) = 0;

	virtual bool DeserializeBody(BitStream *stream) = 0;
	virtual void SerializeBody(BitStream *stream) = 0;
};