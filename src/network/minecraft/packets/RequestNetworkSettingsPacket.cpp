#include <network/minecraft/packets/RequestNetworkSettingsPacket.h>

uint32_t RequestNetworkSettingsPacket::GetID() const
{
	return ID_REQUEST_NETWORK_SETTINGS;
}

void RequestNetworkSettingsPacket::deserialize(BitStream *stream)
{
	stream->ResetReadPointer();
	this->deserializeHeader(stream);
	this->deserializeBody(stream);
}

void RequestNetworkSettingsPacket::serialize(BitStream *stream)
{
	stream->Reset();
	this->serializeHeader(stream);
	this->serializeBody(stream);
	this->serialized = true;
}

void RequestNetworkSettingsPacket::deserializeHeader(BitStream *stream)
{
	uint32_t receivedID = BitStreamHelper::ReadUnsignedVarInt(stream);
	if (receivedID != this->GetID())
	{
		throw InvalidPacketIDException("Invalid PacketID received");
	}
}

void RequestNetworkSettingsPacket::serializeHeader(BitStream *stream)
{
	BitStreamHelper::WriteUnsignedVarInt(this->GetID(), stream);
}

void RequestNetworkSettingsPacket::deserializeBody(BitStream *stream)
{
	if (!stream->Read<int32_t>(this->protocolVersion))
	{
		this->logger->Debug("Unable to read protocol version from RequestNetworkSettingsPacket.\n");
	}
}

void RequestNetworkSettingsPacket::serializeBody(BitStream *stream)
{
	stream->Write<int32_t>(this->protocolVersion);
}

int32_t RequestNetworkSettingsPacket::GetProtocolVersion()
{
	return this->protocolVersion;
}