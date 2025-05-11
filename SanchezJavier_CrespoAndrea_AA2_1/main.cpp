#include <iostream>
#include <Windows.h>
#include "Map.h"

void UpdateScreen ( Map & map , Player & player )
{
    system ( "cls" );
    map.DrawFieldOfView ( player );
    std::cout << "Money: " << player.GetMoney() << std::endl;
}

void NPCMovement ( Map & map )
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
void main()
{
    srand ( time ( NULL ) );
	//APLICAR GAMELOOP
    Map map;
    Vector2 initialPos = { 1, 1 };
    Player player ( initialPos );
    map.GetMap ( ) [ initialPos.y ][ initialPos.x ] = PLAYER;

    map.DrawAllMapVisuals ( );
	//INITIALIZE
	while (true)
	{
		//INPUTS
        if ( GetAsyncKeyState ( VK_UP ))
        {
            Vector2 newPos = { player.GetPosition().x, player.GetPosition ( ).y - 1 };
            
            if ( map.IsValidPosition ( newPos, &player ) )
            {
                map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                player.Move ( newPos );
                player.SetSymbol ( '^' );
                map.GetMap ( ) [ newPos.y ][ newPos.x ] = PLAYER;
            }
            NPCMovement(map);
            UpdateScreen ( map , player );
        }

        else if ( GetAsyncKeyState ( VK_DOWN ))
        {
            Vector2 newPos = { player.GetPosition ( ).x, player.GetPosition ( ).y + 1 };
            if ( map.IsValidPosition(newPos, &player))
            {
                map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                player.Move ( newPos );
                player.SetSymbol ( 'v' );
                map.GetMap ( ) [ newPos.y ][ newPos.x ] = PLAYER;
            }
            NPCMovement(map);
            UpdateScreen ( map , player );
        }

        else if ( GetAsyncKeyState ( VK_RIGHT ))
        {
            Vector2 newPos = { player.GetPosition ( ).x + 1, player.GetPosition ( ).y };
            if ( map.IsValidPosition(newPos, &player))
            {
                map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                player.Move ( newPos );
                player.SetSymbol ( '>' );
                map.GetMap ( ) [ newPos.y ][ newPos.x ] = PLAYER;
            }
            NPCMovement(map);
            UpdateScreen ( map , player );
        }

        else if ( GetAsyncKeyState ( VK_LEFT ))
        {
            Vector2 newPos = { player.GetPosition ( ).x - 1, player.GetPosition ( ).y };
            if ( map.IsValidPosition(newPos, &player))
            {
                map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                player.Move ( newPos );
                player.SetSymbol ( '<' );
                map.GetMap ( ) [ newPos.y ][ newPos.x ] = PLAYER;
            }
            NPCMovement(map);
            UpdateScreen ( map , player );
        }

        else if ( GetAsyncKeyState ( VK_SPACE ) )//Attack
        {
            std::vector<Pedestrian>& pedestrianSFList = map.GetPedestrianSFList();
            std::vector<Pedestrian>& pedestrianLSList = map.GetPedestrianLSList();

            if (pedestrianSFList.empty() || pedestrianLSList.empty()) return;

            for ( int i = 0; i < pedestrianLSList.size ( ); i++ )
            {
                if ( map.NextToPlayer ( pedestrianLSList [ i ] ) )
                {
                    Pedestrian p = pedestrianLSList [ i ];
                    p.SetActive ( false );
                    map.GetMap ( ) [ p.GetPosition ( ).y ][ p.GetPosition ( ).x ] = EMPTY;
                    system ( "cls" );
                    map.GetMap ( ) [ p.GetPosition ( ).y ][ p.GetPosition ( ).x ] = MONEY;
                    pedestrianLSList.erase ( pedestrianLSList.begin ( ) + i );
                    map.SpawnPedestrianToMap(1, pedestrianLSList, 0, true);
                    UpdateScreen ( map , player );
                }
            }
            for (int i = 0; i < pedestrianSFList.size(); i++)
            {
                if (map.NextToPlayer(pedestrianSFList[i]))
                {
                    Pedestrian p = pedestrianSFList[i];
                    p.SetActive(false);
                    
                    map.GetMap()[p.GetPosition().y][p.GetPosition().x] = EMPTY;
                    system("cls");
                    map.GetMap()[p.GetPosition().y][p.GetPosition().x] = MONEY;
                    pedestrianSFList.erase(pedestrianSFList.begin() + i);
                    map.SpawnPedestrianToMap(1, pedestrianLSList, 0, false);
                    UpdateScreen(map, player);
                }
            }
            
        }
        else if ( GetAsyncKeyState ( VK_ESCAPE ) ) //Exit game
        {
            break;
        }

		//RENDER
        
		//FRAMERATE
        Sleep ( 60 );
	}
}
