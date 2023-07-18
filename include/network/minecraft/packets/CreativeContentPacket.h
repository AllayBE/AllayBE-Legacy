#pragma once

#include "MinecraftPacket.h"
#include <nbt/list/Compound.h>
#include <network/minecraft/structs/CreativeContentEntry.h>
#include <vector>

typedef std::vector<CreativeContentEntry> CreativeContentEntryList_t;

class CreativeContentPacket : public MinecraftPacket
{
protected:
	CreativeContentEntryList_t entryList; // todo

public:
	virtual uint32_t GetID() const override;

	virtual void DeserializeHeader(BitStream *stream) override { MinecraftPacket::DeserializeHeader(stream); }
	virtual void SerializeHeader(BitStream *stream) override { MinecraftPacket::SerializeHeader(stream); }

	virtual bool DeserializeBody(BitStream *stream) override;
	virtual void SerializeBody(BitStream *stream) override;

	void SetEntryList(CreativeContentEntryList_t entryList);

	CreativeContentEntryList_t GetEntryList();
};