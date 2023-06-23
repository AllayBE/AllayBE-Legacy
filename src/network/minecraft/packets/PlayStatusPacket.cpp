#include <network/minecraft/packets/PlayStatusPacket.h>

uint32_t PlayStatusPacket::GetID() const
{
	return ID_PLAY_STATUS;
}

bool PlayStatusPacket::DeserializeBody(BitStream *stream)
{
	if (!stream->Read<uint8_t>(this->status))
	{
		return false;
	}
	return true;
}

void PlayStatusPacket::SerializeBody(BitStream *stream)
{
	stream->Write<uint8_t>(this->status);
}

void PlayStatusPacket::SetStatus(uint8_t value)
{
	this->status = value;
}

uint8_t PlayStatusPacket::GetStatus()
{
	return this->status;
}