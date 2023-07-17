#pragma once

#include "Tag.h"
#include <BitStream.h>
#include <cstdint>
#include <misc/BitStreamHelper.h>
#include <nbt/NbtTagDefinitions.h>
#include <string>

using namespace RakNet;

class Int32 : public Tag
{
protected:
	std::string name;
	int32_t value;

public:
	Int32(std::string name, int32_t value);

	virtual int8_t GetID() const override;

	virtual bool DeserializeHeader(BitStream *stream) override { return Tag::DeserializeHeader(stream); };
	virtual bool DeserializeBE(BitStream *stream, bool withHeader) override;
	virtual bool DeserializeLE(BitStream *stream, bool withHeader) override;
	virtual bool DeserializeNET(BitStream *stream, bool withHeader) override;

	virtual void SerializeHeader(BitStream *stream) override { Tag::SerializeHeader(stream); };
	virtual void SerializeBE(BitStream *stream, bool withHeader) override;
	virtual void SerializeLE(BitStream *stream, bool withHeader) override;
	virtual void SerializeNET(BitStream *stream, bool withHeader) override;

	int32_t GetValue();
};