#include <network/minecraft/packets/RequestNetworkSettingsPacket.h>

uint32_t RequestNetworkSettingsPacket::GetID() const
{
	return ID_REQUEST_NETWORK_SETTINGS;
}

bool RequestNetworkSettingsPacket::DeserializeBody(BitStream *stream)
{
	if (!stream->Read<int32_t>(this->protocolVersion))
	{
		return false;
	}
	return true;
}

void RequestNetworkSettingsPacket::SerializeBody(BitStream *stream)
{
	stream->Write<int32_t>(this->protocolVersion);
}

void RequestNetworkSettingsPacket::SetProtocolVersion(int32_t value)
{
	this->protocolVersion = value;
}

int32_t RequestNetworkSettingsPacket::GetProtocolVersion()
{
	return this->protocolVersion;
}