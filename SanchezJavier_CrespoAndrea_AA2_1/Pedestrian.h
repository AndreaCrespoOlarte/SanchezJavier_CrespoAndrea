#pragma once
#include "Vector2.h"

class Pedestrian
{
private:
	Vector2 position;
	int money;
	
public:
	bool active;
	Vector2 GetPosition ( )
	{
		return position;
	}
	void SetPosition ( int x , int y )
	{
		position.x = x;
		position.y = y;
	}

	bool GetActive ( )
	{
		return active;
	}
	void SetActive ( bool isActived )
	{
		active = isActived;
	}
	Pedestrian ( Vector2 _position, int _money ) : position ( _position ) , active ( true ), money (_money) { }
	void Move ( Vector2 newPos );
	bool CheckColision ( );
	int GetMoney ( )
	{
		return money;
	}
};