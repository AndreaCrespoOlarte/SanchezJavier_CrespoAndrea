#pragma once
#include "Vector2.h"

class Pedestrian //Peatones
{
private:
	Vector2 position;
	bool active;
	int money;
	int hp;
	bool agressive;
	int fullhp;
	bool bigSmoke;

public:
	Pedestrian ( const Vector2 _position , const int _money , const int _hp , const bool _agressive , const int _fullhp , const bool _bigSmoke );

	Vector2 GetPosition ( ) const;
	void SetPosition ( int x , int y );
	bool GetActive ( ) const;
	void SetActive ( bool isActived );
	int GetMoney ( ) const;
	int GetHP ( ) const;
	void SetHP ( int v );
	bool GetBehavior ( ) const;
	bool IsBigSmoke ( ) const;
	void Move ( Vector2 newPos );
	bool CanAttack ( Vector2 playerPos ) const;
};