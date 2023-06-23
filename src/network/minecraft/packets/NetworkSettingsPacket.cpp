#include <network/minecraft/packets/NetworkSettingsPacket.h>

uint32_t NetworkSettingsPacket::GetID() const
{
	return ID_NETWORK_SETTINGS;
}

bool NetworkSettingsPacket::DeserializeBody(BitStream *stream)
{
	if (!BitStreamHelper::ReadLittleEndian<uint16_t>(this->compressionThreshold, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadLittleEndian<uint16_t>(this->compressionAlgorithm, stream))
	{
		return false;
	}
	if (!stream->Read<bool>(this->clientThrottle))
	{
		return false;
	}
	if (!stream->Read<uint8_t>(this->clientThrottleThreshold))
	{
		return false;
	}
	if (!stream->Read<float>(this->clientThrottleScalar))
	{
		return false;
	}
	return true;
}

void NetworkSettingsPacket::SerializeBody(BitStream *stream)
{
	BitStreamHelper::WriteLittleEndian<uint16_t>(this->compressionThreshold, stream);
	BitStreamHelper::WriteLittleEndian<uint16_t>(this->compressionAlgorithm, stream);
	stream->Write<bool>(this->clientThrottle);
	stream->Write<uint8_t>(this->clientThrottleThreshold);
	stream->Write<float>(this->clientThrottleScalar);
}

void NetworkSettingsPacket::SetCompressionThreshold(uint16_t value)
{
	this->compressionThreshold = value;
}

void NetworkSettingsPacket::SetCompressionAlgorithm(uint16_t value)
{
	this->compressionAlgorithm = value;
}

void NetworkSettingsPacket::SetClientThrottle(bool value)
{
	this->clientThrottle = value;
}

void NetworkSettingsPacket::SetClientThrottleThreshold(uint8_t value)
{
	this->clientThrottleThreshold = value;
}

void NetworkSettingsPacket::SetClientThrottleScalar(float value)
{
	this->clientThrottleScalar = value;
}

uint16_t NetworkSettingsPacket::GetCompressionThreshold()
{
	return this->compressionThreshold;
}

uint16_t NetworkSettingsPacket::GetCompressionAlgorithm()
{
	return this->compressionAlgorithm;
}

bool NetworkSettingsPacket::GetClientThrottle()
{
	return this->clientThrottle;
}

uint8_t NetworkSettingsPacket::GetClientThrottleThreshold()
{
	return this->clientThrottleThreshold;
}

float NetworkSettingsPacket::GetClientThrottleScalar()
{
	return this->clientThrottleScalar;
}