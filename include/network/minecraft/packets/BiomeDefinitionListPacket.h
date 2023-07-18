#pragma once

#include "MinecraftPacket.h"
#include <nbt/list/Compound.h>

class BiomeDefinitionListPacket : public MinecraftPacket
{
protected:
	Compound *nbt;

public:
	virtual uint32_t GetID() const override;

	virtual void DeserializeHeader(BitStream *stream) override { MinecraftPacket::DeserializeHeader(stream); }
	virtual void SerializeHeader(BitStream *stream) override { MinecraftPacket::SerializeHeader(stream); }

	virtual bool DeserializeBody(BitStream *stream) override;
	virtual void SerializeBody(BitStream *stream) override;

	void SetNbt(Compound *nbt);

	Compound *GetNbt();
};