#include "Pedestrian.h"
#include <iostream>
bool Pedestrian::CheckColision ( ) //Detector de colisiones Devuelve "true" o "false";
{
	return true;
}

void Pedestrian::Move ( Vector2 newPos )
{
	if (!active) //Solo se mueven si est�n activos
	{
		return;
	}
	position = newPos;

}
