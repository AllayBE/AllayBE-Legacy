#include <network/minecraft/packets/MinecraftPacket.h>

MinecraftPacket::MinecraftPacket()
{
	this->serialized = false;
	this->logger = new Logger("Packet", true);
}

uint32_t MinecraftPacket::GetID() const
{
	return ID_NONE;
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
	if (receivedID != this->GetID())
	{
		throw InvalidPacketIDException("Invalid PacketID received");
	}
}

void MinecraftPacket::serializeHeader(BitStream *stream)
{
	BitStreamHelper::WriteUnsignedVarInt(this->GetID(), stream);
}
