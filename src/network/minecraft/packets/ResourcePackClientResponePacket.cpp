#include <network/minecraft/packets/ResourcePackClientResponsePacket.h>

uint32_t ResourcePackClientResponsePacket::GetID() const
{
	return ID_RESOURCE_PACK_CLIENT_RESPONSE;
}

bool ResourcePackClientResponsePacket::DeserializeBody(BitStream *stream)
{
	if (!stream->Read<uint8_t>(this->responseStatus))
	{
		return false;
	}

	int16_t resourcePackIDSize;
	if (!BitStreamHelper::ReadLittleEndian(resourcePackIDSize, stream))
	{
		return false;
	}
	for (int16_t i = 0; i < resourcePackIDSize; ++i)
	{
		this->resourcePackIDs.push_back(BitStreamHelper::ReadStringVarInt(stream));
	}
	return true;
}

void ResourcePackClientResponsePacket::SerializeBody(BitStream *stream)
{
	stream->Write<uint8_t>(this->responseStatus);

	int32_t resourcePackIDSize = static_cast<int32_t>(this->resourcePackIDs.size());
	BitStreamHelper::WriteUnsignedVarInt(resourcePackIDSize, stream);
	for (int32_t i = 0; i < resourcePackIDSize; ++i)
	{
		BitStreamHelper::WriteStringVarInt(this->resourcePackIDs.at(i), stream);
	}
}

void ResourcePackClientResponsePacket::SetResponseStatus(uint8_t value)
{
	this->responseStatus = value;
}

void ResourcePackClientResponsePacket::SetResourcePackIDs(ResourcePackIDs_t value)
{
	this->resourcePackIDs = value;
}

uint8_t ResourcePackClientResponsePacket::GetResponseStatus()
{
	return this->responseStatus;
}

ResourcePackIDs_t ResourcePackClientResponsePacket::GetResourcePackIDs()
{
	return this->resourcePackIDs;
}