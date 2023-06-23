#include <managers/PacketsHandlerManager.h>

PacketsHandlerManager::PacketsHandlerManager()
{
	this->Add(ID_LOGIN, new LoginPacketHandler());
	this->Add(ID_REQUEST_NETWORK_SETTINGS, new RequestNetworkSettingsPacketHandler());
}

bool PacketsHandlerManager::Add(uint32_t id, PacketHandler *handler)
{
	if (this->list.Has(id))
	{
		return false;
	}

	this->list.SetNew(id, handler);
	return true;
}

bool PacketsHandlerManager::Remove(uint32_t id)
{
	if (!this->list.Has(id))
	{
		return false;
	}

	this->list.Delete(id);
	return true;
}

PacketHandler *PacketsHandlerManager::Get(uint32_t id)
{
	if (!this->list.Has(id))
	{
		return nullptr;
	}

	return this->list.Get(id);
}

PacketHandlerList_t PacketsHandlerManager::GetAll()
{
	return this->list;
}
