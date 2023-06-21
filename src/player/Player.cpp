#include <player/Player.h>

Player::Player(SystemAddress address)
{
	this->address = address;
	this->compressionEnabled = false;
}

void Player::SetCompressionEnabled(bool value)
{
	this->compressionEnabled = value;
}

bool Player::IsCompressionEnabled()
{
	return this->compressionEnabled;
}

SystemAddress Player::GetAddress()
{
	return this->address;
}
