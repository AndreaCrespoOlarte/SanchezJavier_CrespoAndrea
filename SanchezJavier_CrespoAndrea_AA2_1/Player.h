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
	Vector2 position;
public: Vector2 GetPosition ( ) { return position; }
public: Player(Vector2 _position)
{
	position = _position;
}
public: void Move(Vector2 newPos, Map& map);
};