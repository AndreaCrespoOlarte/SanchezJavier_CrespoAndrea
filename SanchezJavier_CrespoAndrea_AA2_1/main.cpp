#include <iostream>
#include <Windows.h>
#include "Map.h"
#include "Header.h"
void main()
{

	//APLICAR GAMELOOP
	Map map = Map(20,20);
	Vector2 initialPos = { 0,0 };
	Player player (initialPos);
	map.GetMap ( ) [ initialPos.x ][ initialPos.y ] = PLAYER;
	map.DrawMap ( );
	map.DrawFieldOfView ( player );
	//INITIALIZE
	while (true)
	{
		//INPUTS
        if (GetAsyncKeyState(VK_UP))
        {
            player.Move(Vector2{ player.GetPosition().x,player.GetPosition().y - 1 }, map);
            map.DrawFieldOfView(player);
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            player.Move(Vector2{ player.GetPosition().x,player.GetPosition().y + 1 }, map);
            map.DrawFieldOfView(player);
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            player.Move(Vector2{ player.GetPosition().x + 1,player.GetPosition().y }, map);
            map.DrawFieldOfView(player);
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            player.Move(Vector2{ player.GetPosition().x,player.GetPosition().y }, map);
            map.DrawFieldOfView(player);
        }
        else if (GetAsyncKeyState(VK_SPACE))
        {
            //Attack
        }
        else if (GetAsyncKeyState(VK_ESCAPE))
        {
            //Exit game
        }

		//Usar GetAsyncKeyState(const);
		//RENDER

		//FRAMERATE
		//Usar Sleep();
	}
}