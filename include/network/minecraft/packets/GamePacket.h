#pragma once

#include "MinecraftPacket.h"
#include <vector>

typedef std::vector<BitStream *> StreamList_t;

class GamePacket : public MinecraftPacket
{
protected:
	bool compressionEnabled;
	StreamList_t streams;

public:
	GamePacket();

	virtual uint32_t GetID() const override;

	virtual void deserializeHeader(BitStream *stream) override;
	virtual void serializeHeader(BitStream *stream) override;

	virtual bool deserializeBody(BitStream *stream) override;
	virtual void serializeBody(BitStream *stream) override;

	void SetCompressionEnabled(bool value);
	void SetStreams(StreamList_t value);

	bool isCompressionEnabled();
	StreamList_t GetStreams();
};