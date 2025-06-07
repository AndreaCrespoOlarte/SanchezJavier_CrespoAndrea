#pragma once
#include "Vector2.h"

class Pedestrian //Peatones
{
private:
	Vector2 position;
	int money;
	int fullhp; 
	int hp; 
	bool agressive; 
	bool bigSmoke; 
	
public:
	bool active;
	Vector2 GetPosition ( ) const
	{
		return position;
	}
	void SetPosition ( int x , int y )
	{
		position.x = x;
		position.y = y;
	}
	bool GetActive ( ) const
	{
		return active;
	}
	void SetActive ( bool isActived )
	{
		active = isActived;
	}
	int GetMoney ( ) const
	{
		return money;
	}
	int GetHP ( ) const
	{
		return hp;
	}
	void SetHP(int v)
	{
		hp = v; 
	}
	bool GetBehavior() const
	{
		return agressive; 
	}
	
	bool IsBigSmoke() const
	{
		return bigSmoke;
	}

	Pedestrian(const Vector2 _position, const int _money, const int _hp, const bool _agressive, const int _fullhp, const bool _bigSmoke) :
		position(_position), active(true), money(_money), hp(_hp), agressive(_agressive), fullhp(_fullhp), bigSmoke(_bigSmoke) {
	}
	void Move ( Vector2 newPos );

	bool canAttack(Vector2 playerPos)
	{
		if (agressive && hp < fullhp)
		{
			return true;
		}
		else return false;
	}
};