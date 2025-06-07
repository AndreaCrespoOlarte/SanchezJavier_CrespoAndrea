#pragma once
#include "Vector2.h"
#include <iostream>
/*

Se movera por el mapa + control básico.
Empezara

CONTROLES
	VK_UP
	VK_DOWN
	VK_LEFT
	VK_RIGHT
	VK_SPACE // ATACAR PEATON
	VK_ESC // SALIR DEL JUEGO

SIMBOLO PLAYER:
	Depende donde mire:
		Mirando arriba "^"
		Mirando abajo "v"
		Mirando derecha ">"
		Mirando izquierda "<"
		Dinero = $
*/
// SETEAR EN ENUM ORIENTACION
enum Orientation
{
	NORTH, // '^'
	SOUTH, // 'v'
	EAST, // '<'
	WEST, // '>'
	ON_CAR //C
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
	Player ()
	{
		position = Vector2{ 1,1 };
		money = 0;
		playerOrientation = NORTH;
		hp = 10; 
	}

	bool GetOnCar() 
	{
		return onCar;
	}
	void SetOnCar(bool v)
	{
		onCar = v;
	}
	Vector2 GetPosition() const {
		return position;
	}
	void Move ( Vector2 newPos );

	Orientation GetOrientation ( ) const
	{
		return playerOrientation;
	}
	void SetOrientation ( Orientation symbol )
	{
		playerOrientation = symbol;
	}
	int GetMoney() const
	{
		return money;
	}
	void AddMoney (int newMoney)
	{
		money += newMoney;
	}
	void PrintMoney ()
	{
		std::cout << "Money: " << GetMoney() << std::endl;
	}

	int GetHP()
	{
		return hp;
	}

	void SetHP( int damage )
	{
		hp -= damage; 
	}
};