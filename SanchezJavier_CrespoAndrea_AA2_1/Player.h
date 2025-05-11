#pragma once
#include "Vector2.h"
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
class Player
{
private:
	char symbolShow;
	Vector2 position;
	int money;
public:
	Player ( const Vector2 _position)
	{
		position = _position;
		money = 0;
		symbolShow = '^';
	}

	Vector2 GetPosition() const {
		return position;
	}
	void Move ( Vector2 newPos );

	char GetSymbol ( ) const
	{
		return symbolShow;
	}
	void SetSymbol ( char symbol )
	{
		symbolShow = symbol;
	}
	int GetMoney() const
	{
		return money;
	}
	void AddMoney (int newMoney)
	{
		money += newMoney;
	}
};