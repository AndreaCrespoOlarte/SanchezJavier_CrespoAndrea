#pragma once
#include "Vector2.h"

class Pedestrian //Peatones
{
private:
	Vector2 position;
	int money;
	
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
	Pedestrian ( const Vector2 _position, const int _money ) : position ( _position ) , active ( true ), money (_money) { }
	void Move ( Vector2 newPos );

};