#include <network/minecraft/packets/MinecraftPacket.h>

const uint32_t MinecraftPacket::id = ID_NONE;

MinecraftPacket::MinecraftPacket()
{
	this->serialized = false;
}

void MinecraftPacket::deserialize(BitStream *stream)
{
	stream->ResetReadPointer();
	this->deserializeHeader(stream);
	this->deserializeBody(stream);
}

void MinecraftPacket::serialize(BitStream *stream)
{
	stream->Reset();
	this->serializeHeader(stream);
	this->serializeBody(stream);
	this->serialized = true;
}

void MinecraftPacket::deserializeHeader(BitStream *stream)
{
	uint32_t receivedID = BitStreamHelper::ReadUnsignedVarInt(stream);
	if (receivedID != this->id)
	{
		throw InvalidPacketIDException("Invalid PacketID received");
	}
}

void MinecraftPacket::serializeHeader(BitStream *stream)
{
	BitStreamHelper::WriteUnsignedVarInt(this->id, stream);
}

void MinecraftPacket::deserializeBody(BitStream *stream)
{
}

void MinecraftPacket::serializeBody(BitStream *stream)
{
}
