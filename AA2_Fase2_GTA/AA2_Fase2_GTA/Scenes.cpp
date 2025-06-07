
#include "Scenes.h"
void Scenes::MostrarPantallaInit() 
{
    time_t startTime = std::time(nullptr);
    const int INIT_SCREEN_DURATION = 3;

    while (std::time(nullptr) - startTime < INIT_SCREEN_DURATION) 
    {
        std::system("cls");

        std::cout << "==========================================" << std::endl
            << "               E N T I   G T A            " << std::endl
            << "==========================================" << std::endl
            << "         Bienvenido al caos de ENTI       " << std::endl
            << "      Roba coches, atraca a peatones...   " << std::endl
            << "      y acaba con el malvado Big Smoke    " << std::endl
            << std::endl
            << "            Cargando juego...             " << std::endl;
    }
    MostrarMenu();
}

void Scenes::MostrarMenu() 
{
    system("cls");
    int opcion;

    std::cout << "=====================================" << std::endl
        << "         BIENVENIDO A ENTI GTA       " << std::endl
        << "=====================================" << std::endl
        << "               MAIN MENU             " << std::endl
        << "-------------------------------------" << std::endl
        << " 1. Iniciar Partida" << std::endl
        << " 2. Salir" << std::endl
        << "-------------------------------------" << std::endl
        << "Seleccione una opcion (1-2): ";

    do 
    {
        std::cin >> opcion;

        switch (opcion) 
        {
            case 1:
                std::cout << "Iniciando partida" << std::endl;
                gameLoop.PlayGame();
                break;
            case 2:
                std::cout << "Saliendo del juego";
                break;
            default:
                std::cout << "Opción no valida" << std::endl;
        }

    } while (opcion != 1 && opcion != 2);
}

void Scenes::MostrarGameOver()
{
    std::system("cls");
    time_t startTime = std::time(nullptr);
    const int GAME_OVER_DURATION = 5;

    while (std::time(nullptr) - startTime < GAME_OVER_DURATION) {
        std::system("cls");

        std::cout << "==========================================" << std::endl
            << "                  GAME OVER               " << std::endl
            << "==========================================" << std::endl
            << "     CJ ha llegado al final del camino.   " << std::endl
            << "    El juego se cerrara automaticamente.  " << std::endl;
    }
}