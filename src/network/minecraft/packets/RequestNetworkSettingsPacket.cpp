#include <network/minecraft/packets/RequestNetworkSettingsPacket.h>

uint32_t RequestNetworkSettingsPacket::GetID() const
{
	return ID_REQUEST_NETWORK_SETTINGS;
}

bool RequestNetworkSettingsPacket::deserializeBody(BitStream *stream)
{
	if (!stream->Read<int32_t>(this->protocolVersion))
	{
		return false;
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