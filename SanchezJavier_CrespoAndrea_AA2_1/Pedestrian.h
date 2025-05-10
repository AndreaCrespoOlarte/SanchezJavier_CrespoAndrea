#pragma once
#include "Vector2.h"
/*

Los peatones se a�adiran en el mapa y se moveran por el mapa independientemente del movimiento del personaje detectado colisiones

A�adiremos un n�mero espec�fico de peatones en cada isla en puntos aleatorios y
cada uno se podr� mover horizontalmente o bien verticalmente.
Para esta fase, lo que se implementar� es:
1. Si el player est� a 1 casilla del peat�n, dicho peat�n parar� su movimiento. El
peat�n reanuda el movimiento si el player se aleja de �l.
2. Si se presiona la tecla de atacar, el peat�n fallecer� y soltar� dinero en el
suelo tras fallecer en la misma posici�n donde estaba.
3. Cuando CJ se coloque en la misma posici�n donde est� el dinero, se sumar�
una cantidad aleatoria de dinero en la cuenta de CJ entre 1 y el m�ximo
dinero establecido en el fichero de configuraci�n para cada isla.
4. Se regenerar� otro peat�n en otro punto de la misma isla.

SIMBOLO
	P
*/
class Pedestrian
{
private:
	Vector2 position;
	bool active;
public:
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
	Pedestrian ( Vector2 _position ) : position ( _position ) , active ( true ) { }
	void Move ( Vector2 newPos );
	bool CheckColision ( ); //Detector de colisiones Devuelve "true" o "false";

};