#pragma once

#include "MinecraftPacket.h"
#include "PacketDefinitions.h"
#include <exceptions/Exceptions.h>
#include <misc/BitStreamHelper.h>
#include <stdexcept>
#include <vector>

#ifndef GAME_PACKET_
#define GAME_PACKET_

typedef std::vector<BitStream *> StreamsList_t;

class GamePacket : public MinecraftPacket
{
protected:
	bool compressionEnabled;
	StreamsList_t streams;

public:
	GamePacket();

	virtual uint32_t GetID() const override;

	virtual void deserialize(BitStream *straem) override;
	virtual void serialize(BitStream *straem) override;

	virtual void deserializeHeader(BitStream *stream) override;
	virtual void serializeHeader(BitStream *stream) override;

	virtual void deserializeBody(BitStream *stream) override;
	virtual void serializeBody(BitStream *stream) override;

	void SetCompressionEnabled(bool value);
	void SetStreams(StreamsList_t value);

	bool isCompressionEnabled();
	StreamsList_t GetStreams();
};

#endif