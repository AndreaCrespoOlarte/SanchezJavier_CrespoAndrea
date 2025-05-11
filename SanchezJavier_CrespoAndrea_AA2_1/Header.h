#include "Map.h"
void UpdateScreen ( Map & map , Player & player ) //Reset de pantalla
{
    system ( "cls" );
    map.DrawFieldOfView ( player );
    std::cout << "Money: " << player.GetMoney ( ) << std::endl;
}

void NPCMovement ( Map & map ) 
/* Función encargada de hacer que el movimiento de los peatones sea aleatorio iterando las dos listas
de tipos de peatones (Los Santos y San Fierro).
*/
{
    std::vector<Pedestrian> & pedestrianSFList = map.GetPedestrianSFList ( );
    std::vector<Pedestrian> & pedestrianLSList = map.GetPedestrianLSList ( );

    for ( int i = 0; i < pedestrianSFList.size ( ); i++ )
    {
        if ( !pedestrianSFList [ i ].active || map.NextToPlayer ( pedestrianSFList [ i ] ) )
            continue;

        Vector2 pos = pedestrianSFList [ i ].GetPosition ( );
        Vector2 newPos = pos;
        int option = rand ( ) % 4;
        switch ( option )
        {
            case 0: newPos.y--; break; // arriba
            case 1: newPos.y++; break; // abajo
            case 2: newPos.x++; break; // derecha
            case 3: newPos.x--; break; // izquierda
        }

        if ( newPos.y > 0 && newPos.y < map.GetHeight ( ) - 1 && newPos.x > 0 && newPos.x < map.GetWidth ( ) - 1 &&
             map.GetMap ( ) [ newPos.y ][ newPos.x ] == EMPTY )
        {
            map.GetMap ( ) [ pos.y ][ pos.x ] = EMPTY;
            pedestrianSFList [ i ].SetPosition ( newPos.x , newPos.y );
            map.GetMap ( ) [ newPos.y ][ newPos.x ] = PEDESTRIAN;
        }
    }

    for ( int i = 0; i < pedestrianLSList.size ( ); i++ )
    {
        if ( !pedestrianLSList [ i ].active || map.NextToPlayer ( pedestrianLSList [ i ] ) )
            continue;

        Vector2 pos = pedestrianLSList [ i ].GetPosition ( );
        Vector2 newPos = pos;
        int option = rand ( ) % 4;
        switch ( option )
        {
            case 0: newPos.y--; break; // arriba
            case 1: newPos.y++; break; // abajo
            case 2: newPos.x++; break; // derecha
            case 3: newPos.x--; break; // izquierda
        }

        if ( newPos.y > 0 && newPos.y < map.GetHeight ( ) - 1 && newPos.x > 0 && newPos.x < map.GetWidth ( ) - 1 &&
             map.GetMap ( ) [ newPos.y ][ newPos.x ] == EMPTY )
        {
            map.GetMap ( ) [ pos.y ][ pos.x ] = EMPTY;
            pedestrianLSList [ i ].SetPosition ( newPos.x , newPos.y );
            map.GetMap ( ) [ newPos.y ][ newPos.x ] = PEDESTRIAN;
        }
    }
}
