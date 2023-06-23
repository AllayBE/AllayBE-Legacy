#include <network/minecraft/packets/GamePacket.h>

GamePacket::GamePacket()
{
	this->compressionEnabled = false;
}

uint32_t GamePacket::GetID() const
{
	return ID_GAME;
}

void GamePacket::DeserializeHeader(BitStream *stream)
{
	uint8_t receivedID;
	if (!stream->Read<uint8_t>(receivedID))
	{
		return;
	}
	if (receivedID != this->GetID())
	{
		throw InvalidPacketIDException("Invalid PacketID received");
	}
}

void GamePacket::SerializeHeader(BitStream *stream)
{
	stream->Write<uint8_t>(this->GetID());
}

// TODO: This is expiremntal
bool GamePacket::DeserializeBody(BitStream *stream)
{
	BitSize_t unreadBytes = BITS_TO_BYTES(stream->GetNumberOfUnreadBits());
	char *remainingBuffer = (char *)rakMalloc_Ex(unreadBytes, _FILE_AND_LINE_);
	if (!stream->ReadAlignedBytes((unsigned char *)remainingBuffer, !this->compressionEnabled ? unreadBytes : unreadBytes >> 3))
	{
		return false;
	}

	if (this->compressionEnabled)
	{
		char *decompressedBuffer = (char *)rakMalloc_Ex(unreadBytes, _FILE_AND_LINE_);
		libdeflate_result result = LibDeflateHelper::InflateRaw(remainingBuffer, unreadBytes, decompressedBuffer, unreadBytes);

		// if (result != LIBDEFLATE_SUCCESS)
		// {
		// 	printf("failed to decompress gamepacket\n");
		// 	return false;
		// }

		remainingBuffer = decompressedBuffer;
	}

	BitStream *dataStream = new BitStream((unsigned char *)remainingBuffer, unreadBytes, true);
	rakFree_Ex(remainingBuffer, _FILE_AND_LINE_);

	while (dataStream->GetNumberOfUnreadBits() > 0)
	{
		try
		{
			uint32_t packetLength = BitStreamHelper::ReadUnsignedVarInt(dataStream);
			if (packetLength < 1)
			{
				this->streams.push_back(new BitStream(nullptr, 0, false));
				continue;
			}
			char *packetBuffer = (char *)rakMalloc_Ex(packetLength, _FILE_AND_LINE_);
			if (!dataStream->ReadAlignedBytes((unsigned char *)packetBuffer, packetLength))
			{
				continue;
			}
			BitStream *packetStream = new BitStream((unsigned char *)packetBuffer, packetLength, true);
			rakFree_Ex(packetBuffer, _FILE_AND_LINE_);

			this->streams.push_back(packetStream);
		}
		catch (std::runtime_error error)
		{
			this->streams.push_back(new BitStream(nullptr, 0, false));
		}
	}
	return true;
}

void GamePacket::SerializeBody(BitStream *stream)
{
	for (const auto &packetStream : this->streams)
	{
		BitSize_t bytesUsed = BITS_TO_BYTES(packetStream->GetNumberOfBitsUsed());
		BitStreamHelper::WriteUnsignedVarInt(bytesUsed, stream);

		if (this->compressionEnabled)
		{
			char *compressedBuffer = (char *)rakMalloc_Ex(bytesUsed, _FILE_AND_LINE_);
			size_t compressionSize = LibDeflateHelper::DeflateRaw((char *)packetStream->GetData(), bytesUsed, compressedBuffer);
			stream->WriteAlignedBytes((unsigned char *)compressedBuffer, (const unsigned int)compressionSize);
			rakFree_Ex(compressedBuffer, _FILE_AND_LINE_);
		}
		else
		{
			stream->WriteAlignedBytes(packetStream->GetData(), bytesUsed);
		}
	}
}

void GamePacket::SetCompressionEnabled(bool value)
{
	this->compressionEnabled = value;
}

void GamePacket::SetStreams(StreamList_t value)
{
	this->streams = value;
}

bool GamePacket::isCompressionEnabled()
{
	return this->compressionEnabled;
}

StreamList_t GamePacket::GetStreams()
{
	return this->streams;
}