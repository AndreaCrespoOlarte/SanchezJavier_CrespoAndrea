#pragma once
#include "Vector2.h"
/*

Los peatones se añadiran en el mapa y se moveran por el mapa independientemente del movimiento del personaje detectado colisiones

Añadiremos un número específico de peatones en cada isla en puntos aleatorios y
cada uno se podrá mover horizontalmente o bien verticalmente.
Para esta fase, lo que se implementará es:
1. Si el player está a 1 casilla del peatón, dicho peatón parará su movimiento. El
peatón reanuda el movimiento si el player se aleja de él.
2. Si se presiona la tecla de atacar, el peatón fallecerá y soltará dinero en el
suelo tras fallecer en la misma posición donde estaba.
3. Cuando CJ se coloque en la misma posición donde está el dinero, se sumará
una cantidad aleatoria de dinero en la cuenta de CJ entre 1 y el máximo
dinero establecido en el fichero de configuración para cada isla.
4. Se regenerará otro peatón en otro punto de la misma isla.

SIMBOLO
	P
*/
class Pedestrian
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