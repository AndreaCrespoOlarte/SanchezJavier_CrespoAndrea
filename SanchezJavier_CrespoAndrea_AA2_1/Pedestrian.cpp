#include "Pedestrian.h"
#include <iostream>
void Pedestrian::Move ( Vector2 newPos )
{
	if (!active)
	{
		return;
	}
	position = newPos;
}
