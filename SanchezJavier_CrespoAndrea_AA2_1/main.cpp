#include <iostream>
#include <Windows.h>
#include "Header.h"

void main()
{
    const int FPS_Desired = 60; //A cuántos FPS quieres que vaya el juego
    srand ( time ( NULL ) );
    Map map;
    Vector2 initialPos = { 1, 1 };
    Player player ( initialPos );
    map.GetMap ( ) [ initialPos.y ][ initialPos.x ] = PLAYER;
    map.DrawAllMapVisuals ( ); //Para que se vea todo el mapa antes de comenzar a jugar

	//GAMELOOP
	//INITIALIZE
	while (true)
	{
		//INPUTS
        if ( GetAsyncKeyState ( VK_UP )) //Arriba
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

        else if ( GetAsyncKeyState ( VK_DOWN )) //Abajo
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

        else if ( GetAsyncKeyState ( VK_RIGHT )) //Derecha
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

        else if ( GetAsyncKeyState ( VK_LEFT )) //Izquierda
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

        else if ( GetAsyncKeyState ( VK_SPACE ) )//Ataque
        {
            std::vector<Pedestrian>& pedestrianSFList = map.GetPedestrianSFList();
            std::vector<Pedestrian>& pedestrianLSList = map.GetPedestrianLSList();

            if (pedestrianSFList.empty() || pedestrianLSList.empty()) return;

            for ( int i = 0; i < pedestrianLSList.size ( ); i++ ) 
            {
                //Comprueba si hay un peaton adyacente iterando en ambas listas
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
            system ( "cls" );
            std::cout << "HAS SALIDO DEL JUEGO" << std::endl;
            break;
        }

		//RENDER
        
		//FRAMERATE
        Sleep ( (1000 / FPS_Desired) );
	}
}
