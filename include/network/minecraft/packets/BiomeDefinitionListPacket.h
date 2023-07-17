#pragma once

#include "MinecraftPacket.h"
#include <string>

class BiomeDefinitionListPacket : public MinecraftPacket
{
protected:
	int nbt; // todo

public:
	virtual uint32_t GetID() const override;

	virtual void DeserializeHeader(BitStream *stream) override { MinecraftPacket::DeserializeHeader(stream); }
	virtual void SerializeHeader(BitStream *stream) override { MinecraftPacket::SerializeHeader(stream); }

	virtual bool DeserializeBody(BitStream *stream) override;
	virtual void SerializeBody(BitStream *stream) override;
};