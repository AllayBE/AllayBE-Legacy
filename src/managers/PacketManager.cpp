#include <managers/PacketManager.h>

PacketManager::PacketManager()
{
	this->packetsHandlerManager = new PacketsHandlerManager();

	this->Add(ID_LOGIN, new LoginPacket());
	this->Add(ID_PLAY_STATUS, new PlayStatusPacket());
	this->Add(ID_RESOURCE_PACKS_INFO, new ResourcePacksInfoPacket());
	this->Add(ID_NETWORK_SETTINGS, new NetworkSettingsPacket());
	this->Add(ID_REQUEST_NETWORK_SETTINGS, new RequestNetworkSettingsPacket());
	this->Add(ID_RESOURCE_PACK_STACK, new ResourcePackStackPacket());
	this->Add(ID_RESOURCE_PACK_CLIENT_RESPONSE, new ResourcePackClientResponsePacket());
	this->Add(ID_START_GAME, new StartGamePacket());
	this->Add(ID_BIOME_DEFINITION_LIST, new BiomeDefinitionListPacket());
	this->Add(ID_CREATIVE_CONTENT, new CreativeContentPacket());
}

PacketManager::~PacketManager()
{
	this->list.Clear();
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
				packet->Deserialize(stream);
				PacketHandler *handler = this->packetsHandlerManager->Get(id);

				if (handler != nullptr)
				{
					handler->ProcessPacket(packet, player);
				}
			}
		}
		catch (std::runtime_error error)
		{
		}
	}
}