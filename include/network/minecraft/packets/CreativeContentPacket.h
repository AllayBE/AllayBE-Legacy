#pragma once

#include "MinecraftPacket.h"
#include <string>

class CreativeContentPacket : public MinecraftPacket
{
protected:
	int entry; // todo

public:
	virtual uint32_t GetID() const override;

	virtual void DeserializeHeader(BitStream *stream) override { MinecraftPacket::DeserializeHeader(stream); }
	virtual void SerializeHeader(BitStream *stream) override { MinecraftPacket::SerializeHeader(stream); }

	virtual bool DeserializeBody(BitStream *stream) override;
	virtual void SerializeBody(BitStream *stream) override;
};