#include <managers/PacketManager.h>

PacketManager::PacketManager()
{
	this->packetsHandlerManager = new PacketsHandlerManager();

	this->Add(ID_REQUEST_NETWORK_SETTINGS, new RequestNetworkSettingsPacket());
}

bool PacketManager::Add(uint32_t id, MinecraftPacket *packet)
{
	if (this->list.Has(id))
	{
		return false;
	}

	this->list.SetNew(id, packet);
	return true;
}

bool PacketManager::Remove(uint32_t id)
{
	if (!this->list.Has(id))
	{
		return false;
	}

	this->list.Delete(id);
	return true;
}

MinecraftPacket *PacketManager::Get(uint32_t id)
{
	if (!this->list.Has(id))
	{
		return nullptr;
	}

	return this->list.Get(id);
}

PacketList_t PacketManager::GetAll()
{
	return this->list;
}

PacketsHandlerManager *PacketManager::GetPacketsHandlerManager()
{
	return this->packetsHandlerManager;
}

void PacketManager::HandleGameStreams(StreamList_t streams, Player *player)
{
	for (const auto &stream : streams)
	{
		if (stream->GetData() == nullptr)
		{
			continue;
		}
		try
		{
			uint32_t id = BitStreamHelper::ReadUnsignedVarInt(stream);
			if (this->list.Has(id))
			{
				MinecraftPacket *packet = this->Get(id);
				packet->deserialize(stream);
				PacketHandler *handler = this->packetsHandlerManager->Get(id);

				if (handler != nullptr)
				{
					handler->processPacket(packet, player);
				}
			}
		}
		catch (std::runtime_error error)
		{
		}
	}
}