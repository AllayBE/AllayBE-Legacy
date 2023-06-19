#pragma once

#include <misc/BitStreamHelper.h>
#include "PacketDefinitions.h"
#include <exceptions/Exceptions.h>
#include <vector>

#ifndef GAME_PACKET_
#define GAME_PACKET_

class GamePacket
{
public:
	static const uint32_t id;
	bool serialized;
	bool compressionEnabled;
	std::vector<BitStream *> streams;

public:
	GamePacket();

	void deserialize(BitStream *straem);
	void serialize(BitStream *straem);

	void deserializeHeader(BitStream *stream);
	void serializeHeader(BitStream *stream);

	void deserializeBody(BitStream *stream);
	void serializeBody(BitStream *stream);
};

#endif