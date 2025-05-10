#include "Pedestrian.h"
#include <iostream>
bool Pedestrian::CheckColision ( )
{
	return true;
}//Detector de colisiones Devuelve "true" o "false";

void Pedestrian::Move ( Vector2 newPos )
{
	position = newPos;
	//int option = rand ( ) % 4;
	//Vector2 vector = position;
	//do
	//{
	//	switch ( option )
	//	{
	//		case 0: //Arriba
	//			vector.y--;
	//			break; //Abajo
	//		case 1:
	//			vector.y++;
	//			break;
	//		case 2: //Derecha
	//			vector.x++;
	//			break;
	//		case 3: //Izquiera
	//			vector.x--;
	//			break;
	//		default:
	//			break;
	//	}
	//}
	//while ( !IsValidPosition ( position , map ) && vector != position );

	//if ( !IsValidPosition ( position , map ) ) return;

}
