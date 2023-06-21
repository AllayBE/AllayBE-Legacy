#pragma once

#include "MinecraftPacket.h"
#include "PacketDefinitions.h"
#include <cstdint>
#include <exceptions/Exceptions.h>
#include <misc/BitStreamHelper.h>
#include <stdexcept>
#include <vector>

#ifndef REQUEST_NETWORK_SETTINGS_PACKET
#define REQUEST_NETWORK_SETTINGS_PACKET

class RequestNetworkSettingsPacket : public MinecraftPacket
{
protected:
	int32_t protocolVersion;

public:
	virtual uint32_t GetID() const override;

	virtual void deserialize(BitStream *straem) override;
	virtual void serialize(BitStream *straem) override;

	virtual void deserializeHeader(BitStream *stream) override;
	virtual void serializeHeader(BitStream *stream) override;

	virtual void deserializeBody(BitStream *stream) override;
	virtual void serializeBody(BitStream *stream) override;

	int32_t GetProtocolVersion();
};

#endif