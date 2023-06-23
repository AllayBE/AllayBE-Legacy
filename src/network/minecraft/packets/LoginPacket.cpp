#include <network/minecraft/packets/LoginPacket.h>

uint32_t LoginPacket::GetID() const
{
	return ID_LOGIN;
}

bool LoginPacket::DeserializeBody(BitStream *stream)
{
	if (!stream->Read<int32_t>(this->protocolVersion))
	{
		return false;
	}
	uint8_t *byteArray = BitStreamHelper::ReadByteArrayVarInt(stream);
	this->loginTokens.deserialize(new BitStream(byteArray, sizeof(byteArray), false));
	return true;
}

void LoginPacket::SerializeBody(BitStream *stream)
{
	stream->Write<int32_t>(this->protocolVersion);
	uint8_t *byteArray = (uint8_t *)rakMalloc_Ex(8, _FILE_AND_LINE_);
	BitStream *secondStream = new BitStream(byteArray, (const unsigned int)sizeof(byteArray), true);
	rakFree_Ex(byteArray, _FILE_AND_LINE_);
	this->loginTokens.serialize(secondStream);
	BitStreamHelper::WriteByteArrayVarInt(secondStream->GetData(), stream);
}

void LoginPacket::SetProtocolVersion(int32_t value)
{
	this->protocolVersion = value;
}

void LoginPacket::SetLoginTokens(LoginTokens value)
{
	this->loginTokens = value;
}

int32_t LoginPacket::GetProtocolVersion()
{
	return this->protocolVersion;
}

LoginTokens LoginPacket::GetLoginTokens()
{
	return this->loginTokens;
}