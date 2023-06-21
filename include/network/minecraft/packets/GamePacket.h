#pragma once

#include "MinecraftPacket.h"
#include "PacketDefinitions.h"
#include <exceptions/Exceptions.h>
#include <misc/BitStreamHelper.h>
#include <vector>

#ifndef GAME_PACKET_
#define GAME_PACKET_

class GamePacket : public MinecraftPacket
{
public:
	bool compressionEnabled;
	std::vector<BitStream *> streams;

public:
	GamePacket();

	virtual uint32_t GetID() const override;

	virtual void deserialize(BitStream *straem) override;
	virtual void serialize(BitStream *straem) override;

	virtual void deserializeHeader(BitStream *stream) override;
	virtual void serializeHeader(BitStream *stream) override;

	virtual void deserializeBody(BitStream *stream) override;
	virtual void serializeBody(BitStream *stream) override;
};

#endif