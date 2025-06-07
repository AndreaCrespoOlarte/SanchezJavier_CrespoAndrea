#pragma once
#include "Vector2.h"
#include "Map.h"
/*

 L�gica del Coche:
A�adir coches aparcados en el mapa.
Cada isla tendr� un n�mero de coches que aparecer�n en puntos aleatorios de cada isla.
Dicho n�mero se leer� del fichero de configuraci�n.
CJ podr� subir al coche para poder controlarlo cuando est� a 1 casilla de dicho veh�culo. En caso de haber varios coches a distancia uno, escoger� uno aleatoriamente y se subir� a �l.
El player dejar� de verse en el mapa y pasaremos a poder mover el veh�culo.
Para bajar del coche, lo que haremos ser� el proceso inverso, el player volver� a aparecer en el mapa en cualquier casilla libre a distancia 1 del coche y dicho coche ya no se podr� controlar.

1. 1 Movimiento:
En caso de que el player se suba a un coche, �ste se podr� mover horizontalmente y verticalmente.
La velocidad del coche ser� la misma que la del player.

1. 2 Atropellar peatones con el coche y recoger dinero:
Para representar un atropello, cuando el player est� controlando un coche y �ste se cruce con un peat�n, dicho peat�n desaparecer� del mapa y dejar� una cantidad de dinero aleatoria en una casilla libre que haya alrededor, teniendo en cuenta la cantidad m�xima de dinero que puede dejar en una isla seg�n el fichero de configuraci�n.
CJ podr� recoger ese dinero y se sumar� al dinero total que tenga. Nunca podremos recoger el dinero que deja un peat�n si estamos subidos a un coche.


*/

enum Location
{
	LosSantos,
	SanFierro,
	LasVenturas
};
class Car 
{
	Vector2 position;
	Location location;
	bool occupied;
public:
	Car(Vector2 pos, Location loc) : position(pos), location(loc), occupied(false) {};
	Vector2 GetPosition() 
	{
		return position;
	}
};