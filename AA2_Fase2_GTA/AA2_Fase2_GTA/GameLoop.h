#pragma once
#include "Map.h"
#include "Player.h"
class GameLoop
{
private:
	const int NUM_FPS = 60; //A cuántos FPS quieres que vaya el juego
	Map map;
	Player player;

public:
	GameLoop()
	{
	}

	void PlayGame();
};