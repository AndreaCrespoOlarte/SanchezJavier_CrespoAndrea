#include <iostream>
#include <Windows.h>
#include "Map.h"

void UpdateScreen ( Map & map , Player & player )
{
    system ( "cls" );
    map.DrawFieldOfView ( player );
}

void NPCMovement(Map map)
{
    int option = rand() % 4;
    
    for (int i = 0; i < map.GetPedestrianSFList().size() - 1; i++)
    {
        Vector2 vector = map.GetPedestrianSFList()[i].GetPosition();
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
        } while (!map.IsValidPosition(vector) && vector != map.GetPedestrianSFList()[i].GetPosition());
        map.GetPedestrianSFList()[i].SetPosition(vector.x,vector.y);
    }

    for (int i = 0; i < map.GetPedestrianLSList().size() - 1; i++)
    {
        Vector2 vector = map.GetPedestrianLSList()[i].GetPosition();
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
        } while (!map.IsValidPosition(vector) && vector != map.GetPedestrianLSList()[i].GetPosition());
        map.GetPedestrianLSList()[i].SetPosition(vector.x, vector.y);
    }
}

void main()
{

	//APLICAR GAMELOOP
    Map map;
    Vector2 initialPos = { 1, 1 };
    Player player ( initialPos );
    map.GetMap ( ) [ initialPos.y ][ initialPos.x ] = PLAYER;

    system ( "cls" );
    map.DrawAllMapVisuals ( );
	//INITIALIZE
	while (true)
	{
		//INPUTS
        if ( GetAsyncKeyState ( VK_UP ) & 0x8000 )
        {
            NPCMovement(map);
            Vector2 newPos = { player.GetPosition ( ).x, player.GetPosition ( ).y - 1 };
            if ( map.IsValidPosition ( newPos ) )
            {
                map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                player.Move ( newPos );
                player.SetSymbol ( '^' );
                map.GetMap ( ) [ newPos.y ][ newPos.x ] = PLAYER;
                UpdateScreen ( map , player );
            }
        }

        else if ( GetAsyncKeyState ( VK_DOWN ) & 0x8000 )
        {
            NPCMovement(map);
            Vector2 newPos = { player.GetPosition ( ).x, player.GetPosition ( ).y + 1 };
            if ( map.IsValidPosition ( newPos ) )
            {
                map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                player.Move ( newPos );
                player.SetSymbol ( 'v' );
                map.GetMap ( ) [ newPos.y ][ newPos.x ] = PLAYER;
                UpdateScreen ( map , player );
            }
        }

        else if ( GetAsyncKeyState ( VK_RIGHT ) & 0x8000 )
        {
            NPCMovement(map);
            Vector2 newPos = { player.GetPosition ( ).x + 1, player.GetPosition ( ).y };
            if ( map.IsValidPosition ( newPos ) )
            {
                map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                player.Move ( newPos );
                player.SetSymbol ( '>' );
                map.GetMap ( ) [ newPos.y ][ newPos.x ] = PLAYER;
                UpdateScreen ( map , player );
            }
        }

        else if ( GetAsyncKeyState ( VK_LEFT ) & 0x8000 )
        {
            NPCMovement(map);
            Vector2 newPos = { player.GetPosition ( ).x - 1, player.GetPosition ( ).y };
            if ( map.IsValidPosition ( newPos ) )
            {
                map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                player.Move ( newPos );
                player.SetSymbol ( '<' );
                map.GetMap ( ) [ newPos.y ][ newPos.x ] = PLAYER;
                UpdateScreen ( map , player );
            }
        }

        else if ( GetAsyncKeyState ( VK_SPACE ) )
        {
            //Attack
        }
        else if ( GetAsyncKeyState ( VK_ESCAPE ) )
        {
            //Exit game
            break;
        }

		//Usar GetAsyncKeyState(const);
		//RENDER

		//FRAMERATE
        Sleep ( 60 );
	}
}
