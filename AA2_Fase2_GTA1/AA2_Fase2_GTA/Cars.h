#pragma once
#include "Vector2.h"
#include "Map.h"
/*

 Lógica del Coche:
Añadir coches aparcados en el mapa.
Cada isla tendrá un número de coches que aparecerán en puntos aleatorios de cada isla.
Dicho número se leerá del fichero de configuración.
CJ podrá subir al coche para poder controlarlo cuando esté a 1 casilla de dicho vehículo. En caso de haber varios coches a distancia uno, escogerá uno aleatoriamente y se subirá a él.
El player dejará de verse en el mapa y pasaremos a poder mover el vehículo.
Para bajar del coche, lo que haremos será el proceso inverso, el player volverá a aparecer en el mapa en cualquier casilla libre a distancia 1 del coche y dicho coche ya no se podrá controlar.

1. 1 Movimiento:
En caso de que el player se suba a un coche, éste se podrá mover horizontalmente y verticalmente.
La velocidad del coche será la misma que la del player.

1. 2 Atropellar peatones con el coche y recoger dinero:
Para representar un atropello, cuando el player esté controlando un coche y éste se cruce con un peatón, dicho peatón desaparecerá del mapa y dejará una cantidad de dinero aleatoria en una casilla libre que haya alrededor, teniendo en cuenta la cantidad máxima de dinero que puede dejar en una isla según el fichero de configuración.
CJ podrá recoger ese dinero y se sumará al dinero total que tenga. Nunca podremos recoger el dinero que deja un peatón si estamos subidos a un coche.


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