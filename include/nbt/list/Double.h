#pragma once

#include "Tag.h"
#include <BitStream.h>
#include <cstdint>
#include <misc/BitStreamHelper.h>
#include <nbt/NbtTagDefinitions.h>
#include <string>

using namespace RakNet;

class Double : public Tag
{
protected:
	std::string name;
	double value;

public:
	Double(std::string name, double value);

	virtual int8_t GetID() const override;

	virtual bool DeserializeHeader(BitStream *stream) override { return Tag::DeserializeHeader(stream); };
	virtual bool DeserializeBE(BitStream *stream, bool withHeader) override;
	virtual bool DeserializeLE(BitStream *stream, bool withHeader) override;
	virtual bool DeserializeNET(BitStream *stream, bool withHeader) override;

	virtual void SerializeHeader(BitStream *stream) override { Tag::SerializeHeader(stream); };
	virtual void SerializeBE(BitStream *stream, bool withHeader) override;
	virtual void SerializeLE(BitStream *stream, bool withHeader) override;
	virtual void SerializeNET(BitStream *stream, bool withHeader) override;

	double GetValue();
};