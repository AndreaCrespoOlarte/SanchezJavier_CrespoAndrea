#include "Pedestrian.h"
#include <iostream>
void Pedestrian::Move ( Vector2 newPos )
{
	if (!active) //El peatón solo se mueve si está activo
	{
		return;
	}
	position = newPos;
}
