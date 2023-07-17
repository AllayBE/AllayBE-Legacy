#pragma once

#include "Tag.h"
#include <BitStream.h>
#include <cstdint>
#include <misc/BitStreamHelper.h>
#include <nbt/NbtTagDefinitions.h>
#include <string>
#include <vector>

using namespace RakNet;

typedef std::vector<int8_t> Int8List_t;

class Int8Array : public Tag
{
protected:
	std::string name;
	Int8List_t value;

public:
	Int8Array(std::string name, Int8List_t value);

	virtual int8_t GetID() const override;

	virtual bool DeserializeHeader(BitStream *stream) override { return Tag::DeserializeHeader(stream); };
	virtual bool DeserializeBE(BitStream *stream, bool withHeader) override;
	virtual bool DeserializeLE(BitStream *stream, bool withHeader) override;
	virtual bool DeserializeNET(BitStream *stream, bool withHeader) override;

	virtual void SerializeHeader(BitStream *stream) override { Tag::SerializeHeader(stream); };
	virtual void SerializeBE(BitStream *stream, bool withHeader) override;
	virtual void SerializeLE(BitStream *stream, bool withHeader) override;
	virtual void SerializeNET(BitStream *stream, bool withHeader) override;

	Int8List_t GetValue();
};