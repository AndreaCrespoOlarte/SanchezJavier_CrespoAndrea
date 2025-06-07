#include "Map.h"
const int TIME_TO_MOVE = 1;
time_t lastTime = time(nullptr);

void UpdateMapScreen ( Map & map , Player & player ) //Reset de pantalla
{
    system ( "cls" );
    map.DrawFieldOfView ( player.GetPosition(), player.GetOrientation() );
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

void NPCAttack(Map& map, Player& player)
{
    std::vector<Pedestrian>& pedestrianSFList = map.GetPedestrianSFList();
    std::vector<Pedestrian>& pedestrianLSList = map.GetPedestrianLSList();

    time_t actualTime = time(nullptr);
    
    if (actualTime - lastTime >= TIME_TO_MOVE) //Los NPC atacan cada segundo
    {
        for (int i = 0; i < pedestrianLSList.size(); i++)
        {
            if (pedestrianLSList[i].canAttack(player.GetPosition()) && map.NextToPlayer(pedestrianLSList[i]))
            {
                player.SetHP(1);
            }
        }
        for (int i = 0; i < pedestrianSFList.size(); i++)
        {
            if (pedestrianSFList[i].canAttack(player.GetPosition()) && map.NextToPlayer(pedestrianSFList[i]))
            {
                player.SetHP(1);
            }
        }
    }
}
void KillPedestrianAt ( Vector2 pos , std::vector<Pedestrian> & list , Map & map )
{
    for ( int i = 0; i < list.size ( ); ++i )
    {
        if ( list [ i ].GetPosition ( ) == pos )
        {
            list [ i ].SetActive ( false );                        
            map.GetMap ( ) [ pos.y ][ pos.x ] = EMPTY;
            system ( "cls" );
            map.GetMap ( ) [ pos.y + rand()%2 == 1 && pos.y > 2 ? 1 : -1 ][ pos.x + rand ( ) % 2 == 1 && pos.x > 2 ? 1 : -1 ] = MONEY;
            list.erase ( list.begin ( ) + i );
            map.SpawnPedestrianToMap ( 1 , list , true );
            break;
        }
    }
}