#pragma once

#include "MinecraftPacket.h"

class PlayStatusPacket : public MinecraftPacket
{
protected:
	uint8_t status;

public:
	virtual uint32_t GetID() const override;

	virtual void DeserializeHeader(BitStream *stream) override { MinecraftPacket::DeserializeHeader(stream); }
	virtual void SerializeHeader(BitStream *stream) override { MinecraftPacket::SerializeHeader(stream); }

	virtual bool DeserializeBody(BitStream *stream) override;
	virtual void SerializeBody(BitStream *stream) override;

	void SetStatus(uint8_t value);

	uint8_t GetStatus();
};