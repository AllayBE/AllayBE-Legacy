#include <managers/PlayerManager.h>

size_t PlayerManager::HashAddress(SystemAddress address)
{
	return std::hash<std::string>{}(address.ToString());
}

bool PlayerManager::Has(size_t hashedAddress)
{
	return this->list.Has(hashedAddress);
}

bool PlayerManager::Add(SystemAddress address, RakPeerInterface *peer)
{
	size_t hashedAddress = this->HashAddress(address);
	if (this->Has(hashedAddress))
	{
		return false;
	}

	this->list.SetNew(hashedAddress, new Player(address, hashedAddress, peer));
	return true;
}

bool PlayerManager::Remove(size_t hashedAddress)
{
	if (!this->Has(hashedAddress))
	{
		return false;
	}

	this->list.Delete(hashedAddress);
	return true;
}

Player *PlayerManager::Get(size_t hashedAddress)
{
	if (!this->Has(hashedAddress))
	{
		return nullptr;
	}

	return this->list.Get(hashedAddress);
}

PlayerList_t PlayerManager::GetAll()
{
	return this->list;
}