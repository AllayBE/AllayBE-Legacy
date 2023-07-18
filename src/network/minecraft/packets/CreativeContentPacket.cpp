#include <network/minecraft/packets/CreativeContentPacket.h>

uint32_t CreativeContentPacket::GetID() const
{
	return ID_CREATIVE_CONTENT;
}

bool CreativeContentPacket::DeserializeBody(BitStream *stream)
{
	uint32_t entryListSize = BitStreamHelper::ReadUnsignedVarInt(stream);
	for (uint32_t i = 0; i < entryListSize; ++i)
	{
		Item item = Item::make(0, 0, 0, 0, ItemExtraData::makeWithNbt(ItemExtraDataNbt::make(0, new Compound("", {})), {}, {}, false, 0));
		CreativeContentEntry entry = CreativeContentEntry::make(0, item);
		entry.deserialize(stream);
		this->entryList.push_back(entry);
	}
	return true;
}

void CreativeContentPacket::SerializeBody(BitStream *stream)
{
	uint32_t entryListSize = static_cast<uint32_t>(this->entryList.size());
	BitStreamHelper::WriteUnsignedVarInt(entryListSize, stream);
	for (uint32_t i = 0; i < entryListSize; ++i)
	{
		this->entryList.at(i).deserialize(stream);
	}
}

void CreativeContentPacket::SetEntryList(CreativeContentEntryList_t entryList)
{
	this->entryList = entryList;
}

CreativeContentEntryList_t CreativeContentPacket::GetEntryList()
{
	return this->entryList;
}