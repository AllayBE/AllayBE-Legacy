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

bool GamePacket::DeserializeBody(BitStream *stream)
{
	BitSize_t unreadBits = stream->GetNumberOfUnreadBits();
	uint32_t unreadBytes = !this->compressionEnabled ? BITS_TO_BYTES(unreadBits) : BITS_TO_BYTES(BITS_TO_BYTES(unreadBits));

	uint8_t *remainingBuffer = (uint8_t *)rakMalloc_Ex(unreadBytes, _FILE_AND_LINE_);
	if (!stream->ReadAlignedBytes(remainingBuffer, unreadBytes))
	{
		return false;
	}

	if (this->compressionEnabled)
	{
		uLongf uncompressedSize = unreadBytes * 10;
		Bytef *uncompressedBuffer = (Bytef *)rakMalloc_Ex(uncompressedSize, _FILE_AND_LINE_);

		if (!ZlibHelper::InflateRaw(remainingBuffer, unreadBytes, uncompressedBuffer, uncompressedSize))
		{
			rakFree_Ex(uncompressedBuffer, _FILE_AND_LINE_);
			return false;
		}

		rakFree_Ex(remainingBuffer, _FILE_AND_LINE_);
		remainingBuffer = uncompressedBuffer;
		unreadBytes = uncompressedSize;
	}

	BitStream *dataStream = new BitStream(remainingBuffer, unreadBytes, true);
	rakFree_Ex(remainingBuffer, _FILE_AND_LINE_);

	do
	{
		try
		{
			uint32_t packetLength = BitStreamHelper::ReadUnsignedVarInt(dataStream);
			if (packetLength < 1)
			{
				this->streams.push_back(new BitStream(nullptr, 0, false));
				continue;
			}
			uint8_t *packetBuffer = (uint8_t *)rakMalloc_Ex(packetLength, _FILE_AND_LINE_);
			if (!dataStream->ReadAlignedBytes(packetBuffer, packetLength))
			{
				continue;
			}
			BitStream *packetStream = new BitStream(packetBuffer, packetLength, true);
			rakFree_Ex(packetBuffer, _FILE_AND_LINE_);

			this->streams.push_back(packetStream);
		}
		catch (std::runtime_error error)
		{
			this->streams.push_back(new BitStream(nullptr, 0, false));
		}
	} while (dataStream->GetNumberOfUnreadBits() > 0);
	return true;
}

void GamePacket::SerializeBody(BitStream *stream)
{
	BitStream bs;

	for (const auto &dataStream : this->streams)
	{
		BitSize_t dataSize = dataStream->GetNumberOfBytesUsed();
		BitStreamHelper::WriteUnsignedVarInt(dataSize, &bs);
		bs.WriteAlignedBytes((unsigned char *)dataStream->GetData(), dataSize);
	}

	uint8_t* bsData = bs.GetData();
    BitSize_t bsDataSize = bs.GetNumberOfBytesUsed();
	if (compressionEnabled)
	{
		uLongf compressedSize = compressBound(bsDataSize);
		Bytef *compressedBuffer = (Bytef *)malloc(compressedSize);

		if (ZlibHelper::DeflateRaw(7, bsData, bsDataSize, compressedBuffer, compressedSize))
		{
			BitSize_t compressedSizeBits = BYTES_TO_BITS(compressedSize);
			stream->WriteAlignedBytes(compressedBuffer, compressedSize);
		}

		free(compressedBuffer);
	}
	else
	{
		stream->WriteAlignedBytes(bsData, bsDataSize);
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