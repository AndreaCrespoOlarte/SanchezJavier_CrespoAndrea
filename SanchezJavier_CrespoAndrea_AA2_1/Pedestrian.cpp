#include "Pedestrian.h"
#include <iostream>
bool Pedestrian::CheckColision ( )
{
	return true;
}//Detector de colisiones Devuelve "true" o "false";

void Pedestrian::Move ( Vector2 newPos )
{
	if (!active)
	{
		return;
	}
	position = newPos;

}
