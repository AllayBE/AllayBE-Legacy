#pragma once

#include "MinecraftPacket.h"
#include <string>
#include <vector>

typedef std::vector<std::string> ResourcePackIDs_t;

class ResourcePackClientResponsePacket : public MinecraftPacket
{
protected:
	uint8_t responseStatus;
	ResourcePackIDs_t resourcePackIDs;

public:
	virtual uint32_t GetID() const override;

	virtual void DeserializeHeader(BitStream *stream) override { MinecraftPacket::DeserializeHeader(stream); }
	virtual void SerializeHeader(BitStream *stream) override { MinecraftPacket::SerializeHeader(stream); }

	virtual bool DeserializeBody(BitStream *stream) override;
	virtual void SerializeBody(BitStream *stream) override;

	void SetResponseStatus(uint8_t value);
	void SetResourcePackIDs(ResourcePackIDs_t value);

	uint8_t GetResponseStatus();
	ResourcePackIDs_t GetResourcePackIDs();
};