#include "Pedestrian.h"
#include <iostream>
void Pedestrian::Move ( Vector2 newPos )
{
	if (!active) //El peat�n solo se mueve si est� activo
	{
		return;
	}
	position = newPos;
}
