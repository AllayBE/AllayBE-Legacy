#pragma once

#include <BitStream.h>
#include <cstdint>
#include <stdexcept>

using namespace RakNet;

class Tag
{
public:
	virtual int8_t GetID() const = 0;

	virtual bool DeserializeHeader(BitStream *stream) = 0;
	virtual bool DeserializeBE(BitStream *stream, bool withHeader) = 0;
	virtual bool DeserializeLE(BitStream *stream, bool withHeader) = 0;
	virtual bool DeserializeNET(BitStream *stream, bool withHeader) = 0;

	virtual void SerializeHeader(BitStream *stream) = 0;
	virtual void SerializeBE(BitStream *stream, bool withHeader) = 0;
	virtual void SerializeLE(BitStream *stream, bool withHeader) = 0;
	virtual void SerializeNET(BitStream *stream, bool withHeader) = 0;
};