#pragma once

#include "MinecraftPacket.h"
#include <network/minecraft/structs/LoginTokens.h>

class LoginPacket : public MinecraftPacket
{
protected:
	int32_t protocolVersion;
	LoginTokens loginTokens;

public:
	virtual uint32_t GetID() const override;

	virtual void DeserializeHeader(BitStream *stream) override { MinecraftPacket::DeserializeHeader(stream); }
	virtual void SerializeHeader(BitStream *stream) override { MinecraftPacket::SerializeHeader(stream); }

	virtual bool DeserializeBody(BitStream *stream) override;
	virtual void SerializeBody(BitStream *stream) override;

	void SetProtocolVersion(int32_t value);
	void SetLoginTokens(LoginTokens value);

	int32_t GetProtocolVersion();
	LoginTokens GetLoginTokens();
};