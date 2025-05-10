#include <iostream>
#include <Windows.h>
#include "Map.h"

void UpdateScreen ( Map & map , Player & player )
{
    system ( "cls" );
    map.DrawFieldOfView ( player );
}

void NPCMovement(Map& map)
{
    std::vector<Pedestrian> & pedestrianSFList = map.GetPedestrianSFList ( );
    std::vector<Pedestrian> & pedestrianLSList = map.GetPedestrianLSList ( );

    if ( pedestrianSFList.empty ( ) || pedestrianLSList.empty ( ) ) return;

    for (int i = 0; i < pedestrianSFList.size(); i++)
    {
        int option = rand ( ) % 4;
        if ( map.NextToPlayer ( pedestrianSFList [ i ] ) ) continue;
        Vector2 vector = pedestrianSFList [ i ].GetPosition ( );
        do
        {
            switch (option)
            {
            case 0: //arriba
                vector.y--;
                break; //abajo
            case 1:
                vector.y++;
                break;
            case 2: //derecha
                vector.x++;
                break;
            case 3: //izquierda
                vector.x--;
                break;
            default:
                break;
            }
        } while (!map.IsValidPosition(vector) && vector != pedestrianSFList [i].GetPosition());
        if ( vector.y < 1 || vector.y >= map.GetHeight ( ) || vector.x < 1 || vector.x >= map.GetWidth ( ) )
        {
            continue;
        }
        map.GetMap ( ) [ pedestrianSFList [ i ].GetPosition ( ).y ][ pedestrianSFList [ i ].GetPosition ( ).x ] = EMPTY;
        pedestrianSFList [ i ].SetPosition ( vector.x , vector.y );
        map.GetMap ( ) [ vector.y ][ vector.x ] = PEDESTRIAN;
    }

    for (int i = 0; i < pedestrianLSList.size(); i++)
    {
        int option = rand ( ) % 4;
        if ( map.NextToPlayer ( pedestrianLSList [ i ] ) ) continue;
        Vector2 vector = pedestrianLSList [i].GetPosition();
        do
        {
            switch (option)
            {
            case 0: //arriba
                vector.y--;
                break; //abajo
            case 1:
                vector.y++;
                break;
            case 2: //derecha
                vector.x++;
                break;
            case 3: //izquierda
                vector.x--;
                break;
            default:
                break;
            }
        } while (!map.IsValidPosition(vector) && vector != pedestrianLSList [i].GetPosition());
        if ( vector.y < 1 || vector.y >= map.GetHeight ( ) || vector.x < 1 || vector.x >= map.GetWidth ( ) )
        {
            continue;
        }
        map.GetMap ( ) [ pedestrianLSList [ i ].GetPosition().y ][ pedestrianLSList [ i ].GetPosition ( ).x ] = EMPTY;
        pedestrianLSList [i].SetPosition(vector.x, vector.y);
        map.GetMap ( ) [ vector.y ][ vector.x ] = PEDESTRIAN;
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

    //system ( "cls" );
    map.DrawAllMapVisuals ( );
	//INITIALIZE
	while (true)
	{
		//INPUTS
        if ( GetAsyncKeyState ( VK_UP ) & 0x8000 )
        {
            Vector2 newPos = { player.GetPosition().x, player.GetPosition ( ).y - 1 };
            if ( map.IsValidPosition ( newPos ) )
            {
                map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                player.Move ( newPos );
                player.SetSymbol ( '^' );
                map.GetMap ( ) [ newPos.y ][ newPos.x ] = PLAYER;
                UpdateScreen ( map , player );
            }
            NPCMovement(map);
        }

        else if ( GetAsyncKeyState ( VK_DOWN ) & 0x8000 )
        {
            Vector2 newPos = { player.GetPosition ( ).x, player.GetPosition ( ).y + 1 };
            if ( map.IsValidPosition ( newPos ) )
            {
                map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                player.Move ( newPos );
                player.SetSymbol ( 'v' );
                map.GetMap ( ) [ newPos.y ][ newPos.x ] = PLAYER;
                UpdateScreen ( map , player );
            }
            NPCMovement(map);
        }

        else if ( GetAsyncKeyState ( VK_RIGHT ) & 0x8000 )
        {
            Vector2 newPos = { player.GetPosition ( ).x + 1, player.GetPosition ( ).y };
            if ( map.IsValidPosition ( newPos ) )
            {
                map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                player.Move ( newPos );
                player.SetSymbol ( '>' );
                map.GetMap ( ) [ newPos.y ][ newPos.x ] = PLAYER;
                UpdateScreen ( map , player );
            }
            NPCMovement(map);
        }

        else if ( GetAsyncKeyState ( VK_LEFT ) & 0x8000 )
        {
            Vector2 newPos = { player.GetPosition ( ).x - 1, player.GetPosition ( ).y };
            if ( map.IsValidPosition ( newPos ) )
            {
                map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                player.Move ( newPos );
                player.SetSymbol ( '<' );
                map.GetMap ( ) [ newPos.y ][ newPos.x ] = PLAYER;
                UpdateScreen ( map , player );
            }
            NPCMovement(map);
        }

        else if ( GetAsyncKeyState ( VK_SPACE ) )//Attack
        {
            std::vector<Pedestrian>& pedestrianSFList = map.GetPedestrianSFList();
            std::vector<Pedestrian>& pedestrianLSList = map.GetPedestrianLSList();

            if (pedestrianSFList.empty() || pedestrianLSList.empty()) return;

            for (int i = 0; i < pedestrianSFList.size(); i++)
            {
                if (map.NextToPlayer(pedestrianSFList[i]))
                {
                    Pedestrian p = pedestrianSFList[i];
                    p.SetActive(false);
                    
                    map.GetMap()[p.GetPosition().y][p.GetPosition().x] = EMPTY;
                    //map.DrawMap();
                    map.GetMap()[p.GetPosition().y][p.GetPosition().x] = MONEY;
                    map.DrawFieldOfView(player);
                }
            }

            for (int i = 0; i < pedestrianLSList.size(); i++)
            {
                if (map.NextToPlayer(pedestrianLSList[i]))
                {
                    Pedestrian p = pedestrianLSList[i];
                    p.SetActive(false);

                    map.GetMap()[p.GetPosition().y][p.GetPosition().x] = EMPTY;
                    //map.DrawMap();
                    map.GetMap()[p.GetPosition().y][p.GetPosition().x] = MONEY;
                    map.DrawFieldOfView(player);
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
