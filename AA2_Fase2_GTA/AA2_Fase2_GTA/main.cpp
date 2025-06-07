#include <iostream>
#include "GameLoop.h"
#include "Scenes.h"

int main()
{
    srand ( time ( NULL ) );
    Scenes scene;
    scene.MostrarPantallaInit();
    return 0;
}
