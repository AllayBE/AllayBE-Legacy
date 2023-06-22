#pragma once

#include "MinecraftPacket.h"

class RequestNetworkSettingsPacket : public MinecraftPacket
{
protected:
	int32_t protocolVersion;

public:
	virtual uint32_t GetID() const override;

	virtual void deserializeHeader(BitStream *stream) override { MinecraftPacket::deserializeHeader(stream); }
	virtual void serializeHeader(BitStream *stream) override { MinecraftPacket::serializeHeader(stream); }

	virtual bool deserializeBody(BitStream *stream) override;
	virtual void serializeBody(BitStream *stream) override;

	int32_t GetProtocolVersion();
};