#include "Pedestrian.h"
#include <iostream>

Pedestrian::Pedestrian ( const Vector2 _position , const int _money , const int _hp , const bool _agressive , const int _fullhp , const bool _bigSmoke )
	: position ( _position ) , active ( true ) , money ( _money ) , hp ( _hp ) , agressive ( _agressive ) , fullhp ( _fullhp ) , bigSmoke ( _bigSmoke ){}

Vector2 Pedestrian::GetPosition ( ) const
{
	return position;
}

void Pedestrian::SetPosition ( int x , int y )
{
	position.x = x;
	position.y = y;
}

bool Pedestrian::GetActive ( ) const
{
	return active;
}

void Pedestrian::SetActive ( bool isActived )
{
	active = isActived;
}

int Pedestrian::GetMoney ( ) const
{
	return money;
}

int Pedestrian::GetHP ( ) const
{
	return hp;
}

void Pedestrian::SetHP ( int v )
{
	hp = v;
}

bool Pedestrian::GetBehavior ( ) const
{
	return agressive;
}

bool Pedestrian::IsBigSmoke ( ) const
{
	return bigSmoke;
}

void Pedestrian::Move ( Vector2 newPos )
{
	if ( !active ) //El peatón solo se mueve si está activo
	{
		return;
	}
	position = newPos;
}

bool  Pedestrian::CanAttack ( Vector2 playerPos ) const
{
	return agressive && hp < fullhp;
}
