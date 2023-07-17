#include <network/minecraft/packets/CreativeContentPacket.h>

uint32_t CreativeContentPacket::GetID() const
{
	return ID_CREATIVE_CONTENT;
}

bool CreativeContentPacket::DeserializeBody(BitStream *stream)
{
	return true;
}

void CreativeContentPacket::SerializeBody(BitStream *stream)
{
	// temp
	BitStreamHelper::WriteUnsignedVarInt(0, stream);
}