#pragma once
#include <iostream>
#include "Vector2.h"

enum Orientation
{
	NORTH , // '^'
	SOUTH , // 'v'
	EAST ,  // '<'
	WEST ,  // '>'
	ON_CAR //  'C'
};

class Player
{
private:
	Orientation playerOrientation;
	Vector2 position;
	int money;
	int hp;
	bool onCar;

public:
	Player ( );

	bool GetOnCar ( ) const;
	void SetOnCar ( bool v );

	Vector2 GetPosition ( ) const;
	void Move ( Vector2 newPos );

	Orientation GetOrientation ( ) const;
	void SetOrientation ( Orientation symbol );

	int GetMoney ( ) const;
	void AddMoney ( int newMoney );
	const void PrintMoney ( ) const;

	int GetHP ( ) const;
	void SetHP ( int damage );
};