#pragma once

#include "MinecraftPacket.h"
#include <misc/LibDeflateHelper.h>
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

	virtual void DeserializeHeader(BitStream *stream) override;
	virtual void SerializeHeader(BitStream *stream) override;

	virtual bool DeserializeBody(BitStream *stream) override;
	virtual void SerializeBody(BitStream *stream) override;

	void SetCompressionEnabled(bool value);
	void SetStreams(StreamList_t value);

	bool isCompressionEnabled();
	StreamList_t GetStreams();
};