#pragma once

#include "MinecraftPacket.h"

class PlayStatusPacket : public MinecraftPacket
{
protected:
	int32_t status;

public:
	virtual uint32_t GetID() const override;

	virtual void DeserializeHeader(BitStream *stream) override { MinecraftPacket::DeserializeHeader(stream); }
	virtual void SerializeHeader(BitStream *stream) override { MinecraftPacket::SerializeHeader(stream); }

	virtual bool DeserializeBody(BitStream *stream) override;
	virtual void SerializeBody(BitStream *stream) override;

	void SetStatus(int32_t value);

	int32_t GetStatus();
};