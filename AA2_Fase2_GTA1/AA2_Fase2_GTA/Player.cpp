#include <windows.h>
#include "Player.h"
#include "Player.h"

Player::Player ( )
{
	position = Vector2 { 1, 1 };
	money = 0;
	playerOrientation = NORTH;
	hp = 10;
	onCar = false;
}

bool Player::GetOnCar ( ) const
{
	return onCar;
}

void Player::SetOnCar ( bool v )
{
	onCar = v;
}

Vector2 Player::GetPosition ( ) const
{
	return position;
}

void Player::Move ( Vector2 newPos )
{
	position = newPos;
}

Orientation Player::GetOrientation ( ) const
{
	return playerOrientation;
}

void Player::SetOrientation ( Orientation symbol )
{
	playerOrientation = symbol;
}

int Player::GetMoney ( ) const
{
	return money;
}

void Player::AddMoney ( int newMoney )
{
	money += newMoney;
}

const void Player::PrintMoney ( )  const
{
	std::cout << "Money: " << GetMoney ( ) << std::endl;
}

int Player::GetHP ( ) const
{
	return hp;
}

void Player::SetHP ( int damage )
{
	hp -= damage;
}
