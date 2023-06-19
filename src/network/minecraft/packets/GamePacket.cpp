#include <network/minecraft/packets/GamePacket.h>

const uint32_t GamePacket::id = ID_GAME;

GamePacket::GamePacket()
{
	this->serialized = false;
	this->compressionEnabled = false;
}

void GamePacket::deserialize(BitStream *stream)
{
	stream->ResetReadPointer();
	this->deserializeHeader(stream);
	this->deserializeBody(stream);
}

void GamePacket::serialize(BitStream *stream)
{
	stream->Reset();
	this->serializeHeader(stream);
	this->serializeBody(stream);
	this->serialized = true;
}

void GamePacket::deserializeHeader(BitStream *stream)
{
	uint8_t receivedID;
	if (!stream->Read<uint8_t>(receivedID))
	{
		printf("Unable to read the packet id of game packet\n");
		return;
	}
	if (receivedID != this->id)
	{
		throw InvalidPacketIDException("Invalid PacketID received");
	}
}

void GamePacket::serializeHeader(BitStream *stream)
{
	stream->Write<uint8_t>(this->id);
}

void GamePacket::deserializeBody(BitStream *stream)
{
	BitStream *dataStream;
	BitSize_t unreadBytes = BITS_TO_BYTES(stream->GetNumberOfUnreadBits());
	char *remainingBuffer = (char *)rakMalloc_Ex(unreadBytes, _FILE_AND_LINE_);
	stream->ReadAlignedBytes((unsigned char *)remainingBuffer, unreadBytes);

	if (this->compressionEnabled)
	{
	}
	else
	{
		dataStream = new BitStream((unsigned char *)remainingBuffer, unreadBytes, true);
	}
	rakFree_Ex(remainingBuffer, _FILE_AND_LINE_);

	while (dataStream->GetReadOffset() < unreadBytes) // TODO: Check this
	{
		uint32_t packetLength = BitStreamHelper::ReadUnsignedVarInt(dataStream);
		char *packetBuffer = (char *)rakMalloc_Ex(packetLength, _FILE_AND_LINE_);
		dataStream->ReadAlignedBytes((unsigned char *)packetBuffer, packetLength);
		BitStream *packetStream = new BitStream((unsigned char *)packetBuffer, packetLength, true);
		rakFree_Ex(packetBuffer, _FILE_AND_LINE_);
		this->streams.push_back(packetStream);
	}
}

void GamePacket::serializeBody(BitStream *stream)
{
	for (const auto &packetStream : this->streams)
	{
		BitSize_t bytesUsed = BITS_TO_BYTES(packetStream->GetNumberOfBitsUsed());
		BitStreamHelper::WriteUnsignedVarInt(bytesUsed, stream);

		if (this->compressionEnabled)
		{
		}
		else
		{
			stream->WriteAlignedBytes(packetStream->GetData(), bytesUsed);
		}
	}
}