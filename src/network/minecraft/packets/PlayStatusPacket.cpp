#include <network/minecraft/packets/PlayStatusPacket.h>

uint32_t PlayStatusPacket::GetID() const
{
	return ID_PLAY_STATUS;
}

bool PlayStatusPacket::DeserializeBody(BitStream *stream)
{
	if (!stream->Read<int32_t>(this->status))
	{
		return false;
	}
	return true;
}

void PlayStatusPacket::SerializeBody(BitStream *stream)
{
	stream->Write<int32_t>(this->status);
}

void PlayStatusPacket::SetStatus(int32_t value)
{
	this->status = value;
}

int32_t PlayStatusPacket::GetStatus()
{
	return this->status;
}