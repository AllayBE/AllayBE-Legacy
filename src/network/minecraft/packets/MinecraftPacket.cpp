#include <network/minecraft/packets/MinecraftPacket.h>

uint32_t MinecraftPacket::GetID() const
{
	return ID_NONE;
}

void MinecraftPacket::Deserialize(BitStream *stream)
{
	stream->ResetReadPointer();
	this->DeserializeHeader(stream);
	this->DeserializeBody(stream);
}

void MinecraftPacket::Serialize(BitStream *stream)
{
	stream->Reset();
	this->SerializeHeader(stream);
	this->SerializeBody(stream);
}

void MinecraftPacket::DeserializeHeader(BitStream *stream)
{
	uint32_t receivedID = BitStreamHelper::ReadUnsignedVarInt(stream);
	if (receivedID != this->GetID())
	{
		throw InvalidPacketIDException("Invalid PacketID received");
	}
}

void MinecraftPacket::SerializeHeader(BitStream *stream)
{
	BitStreamHelper::WriteUnsignedVarInt(this->GetID(), stream);
}