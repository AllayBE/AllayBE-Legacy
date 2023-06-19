#include <player/Player.h>

Player::Player(SystemAddress address)
{
	this->address = address;
}

SystemAddress Player::GetAddress()
{
	return this->address;
}
