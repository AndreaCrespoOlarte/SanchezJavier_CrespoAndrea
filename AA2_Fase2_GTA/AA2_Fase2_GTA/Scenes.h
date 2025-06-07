#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GameLoop.h"
class Scenes
{
public:
	GameLoop gameLoop;
	void MostrarPantallaInit();
	void MostrarMenu();
	static void MostrarGameOver();
};