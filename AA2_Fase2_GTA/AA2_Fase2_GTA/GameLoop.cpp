#include "GameLoop.h"
#include "Utils.h"
#include "Scenes.h"
#include <Windows.h>  
#include <ctime>

void GameLoop::PlayGame()
{
    const int TIME_TO_MOVE = 1; //Tiempo maximo para moverse automaticamente
    time_t lastTime = time(nullptr);

    bool spacePressedLastFrame = false;
    bool E_PressedLastFrame = false;
    bool attacked = false;
    //GAMELOOP
    //INITIALIZE

    map.GetMap()[player.GetPosition().y][player.GetPosition().x] = PLAYER;
    map.DrawAllMapVisuals(); //Para que se vea todo el mapa antes de comenzar a jugar
    
    while (true)
    {
        spacePressedLastFrame = GetAsyncKeyState ( VK_SPACE );
        E_PressedLastFrame = GetAsyncKeyState ( 0x45 );
        //if ( attacked && spacePressedLastFrame ) 
        time_t actualTime = time(nullptr);

        if (actualTime - lastTime >= TIME_TO_MOVE) //Los NPC se mueven cada segundo
        {
            attacked = false;
            std::vector<Pedestrian> & pedestrianSFList = map.GetPedestrianSFList ( );
            std::vector<Pedestrian> & pedestrianLSList = map.GetPedestrianLSList ( );

            for ( int i = 0; i < pedestrianSFList.size(); i++ )
            {
                if ( pedestrianSFList [ i ].canAttack ( player.GetPosition ( ) ) ) NPCAttack ( map , player );
            }
            for ( int i = 0; i < pedestrianLSList.size(); i++ )
            {
                if ( pedestrianLSList [ i ].canAttack ( player.GetPosition ( ) ) ) NPCAttack ( map , player );
            }
            NPCMovement(map);
            lastTime = actualTime;
            UpdateMapScreen(map, player);
            player.PrintMoney();
        }

        //INPUTS
       // ARRIBA
        if ( GetAsyncKeyState ( VK_UP ) )
        {
            Vector2 newPos = { player.GetPosition ( ).x, player.GetPosition ( ).y - 1 };
            if ( map.IsValidPosition ( newPos , &player ) )
            {
                std::vector<Pedestrian> & pedestrianSFList = map.GetPedestrianSFList ( );
                std::vector<Pedestrian> & pedestrianLSList = map.GetPedestrianLSList ( );

                if ( player.GetOnCar ( ) && map.GetMap ( ) [ newPos.y ][ newPos.x ] == PEDESTRIAN )
                {
                    KillPedestrianAt ( newPos , pedestrianSFList , map );
                    KillPedestrianAt ( newPos , pedestrianLSList , map );
                }

                player.SetOrientation ( player.GetOnCar ( ) ? ON_CAR : NORTH );
                map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                player.Move ( newPos );
                map.GetMap ( ) [ newPos.y ][ newPos.x ] = PLAYER;
                UpdateMapScreen ( map , player );
                player.PrintMoney ( );
            }
        }

        // ABAJO
        else if ( GetAsyncKeyState ( VK_DOWN ) )
        {
            Vector2 newPos = { player.GetPosition ( ).x, player.GetPosition ( ).y + 1 };
            if ( map.IsValidPosition ( newPos , &player ) )
            {
                std::vector<Pedestrian> & pedestrianSFList = map.GetPedestrianSFList ( );
                std::vector<Pedestrian> & pedestrianLSList = map.GetPedestrianLSList ( );

                if ( player.GetOnCar ( ) && map.GetMap ( ) [ newPos.y ][ newPos.x ] == PEDESTRIAN )
                {
                    KillPedestrianAt ( newPos , pedestrianSFList , map );
                    KillPedestrianAt ( newPos , pedestrianLSList , map );
                }

                player.SetOrientation ( player.GetOnCar ( ) ? ON_CAR : SOUTH );
                map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                player.Move ( newPos );
                map.GetMap ( ) [ newPos.y ][ newPos.x ] = PLAYER;
                UpdateMapScreen ( map , player );
                player.PrintMoney ( );
            }
        }

        // DERECHA
        else if ( GetAsyncKeyState ( VK_RIGHT ) )
        {
            spacePressedLastFrame = false;
            Vector2 newPos = { player.GetPosition ( ).x + 1, player.GetPosition ( ).y };
            if ( map.IsValidPosition ( newPos , &player ) )
            {
                std::vector<Pedestrian> & pedestrianSFList = map.GetPedestrianSFList ( );
                std::vector<Pedestrian> & pedestrianLSList = map.GetPedestrianLSList ( );

                if ( player.GetOnCar ( ) && map.GetMap ( ) [ newPos.y ][ newPos.x ] == PEDESTRIAN )
                {
                    KillPedestrianAt ( newPos , pedestrianSFList , map );
                    KillPedestrianAt ( newPos , pedestrianLSList , map );
                }

                player.SetOrientation ( player.GetOnCar ( ) ? ON_CAR : WEST );
                map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                player.Move ( newPos );
                map.GetMap ( ) [ newPos.y ][ newPos.x ] = PLAYER;
                UpdateMapScreen ( map , player );
                player.PrintMoney ( );
            }
        }

        // IZQUIERDA
        else if ( GetAsyncKeyState ( VK_LEFT ) )
        {
            Vector2 newPos = { player.GetPosition ( ).x - 1, player.GetPosition ( ).y };
            if ( map.IsValidPosition ( newPos , &player ) )
            {
                std::vector<Pedestrian> & pedestrianSFList = map.GetPedestrianSFList ( );
                std::vector<Pedestrian> & pedestrianLSList = map.GetPedestrianLSList ( );

                if ( player.GetOnCar ( ) && map.GetMap ( ) [ newPos.y ][ newPos.x ] == PEDESTRIAN )
                {
                    KillPedestrianAt ( newPos , pedestrianSFList , map );
                    KillPedestrianAt ( newPos , pedestrianLSList , map );
                }

                player.SetOrientation ( player.GetOnCar ( ) ? ON_CAR : EAST );
                map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                player.Move ( newPos );
                map.GetMap ( ) [ newPos.y ][ newPos.x ] = PLAYER;
                UpdateMapScreen ( map , player );
                player.PrintMoney ( );
            }
        }
        else if ( E_PressedLastFrame ) //Tecla E
        {
            E_PressedLastFrame = false;
            Vector2 pos = player.GetPosition ( );

            if ( player.GetOnCar ( ) ) //Se baja del coche pero te lleva al main menu, desconozco el porque
            {
                if ( map.GetMap ( ) [ pos.y ][ pos.x ] == PLAYER )
                {
                    map.GetMap ( ) [ pos.y ][ pos.x ] = EMPTY;
                    system ( "cls" );
                    pos.x += rand ( ) % 2 == 1 ? 1 : -1;
                    pos.y += rand ( ) % 2 == 1 ? 1 : -1;
                    player.Move ( pos );
                    player.SetOnCar ( false );
                    player.SetOrientation ( NORTH );
                    map.GetMap ( ) [ pos.y ][ pos.x ] = PLAYER;
                    UpdateMapScreen ( map , player );
                }
            }
            for ( int dy = -1; dy <= 1; dy++ )
            {
                for ( int dx = -1; dx <= 1; dx++ )
                {
                    if ( dx == 0 && dy == 0 ) continue;

                    int newX = pos.x + dx;
                    int newY = pos.y + dy;
                    Vector2 newPos { newX, newY };

                    if ( map.GetMap ( ) [ newPos.y ][ newPos.x ] == CAR )
                    {
                        map.GetMap ( ) [ newPos.y ][ newPos.x ] = EMPTY;
                        map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = EMPTY;
                        player.SetOnCar ( true );
                        player.SetOrientation ( ON_CAR );
                        map.GetMap ( ) [ player.GetPosition ( ).y ][ player.GetPosition ( ).x ] = CAR;
                        UpdateMapScreen ( map , player );
                        break;
                    }
                }
            }
        }

        else if (spacePressedLastFrame)//Ataque
        {
            spacePressedLastFrame = false;
            std::vector<Pedestrian>& pedestrianSFList = map.GetPedestrianSFList();
            std::vector<Pedestrian>& pedestrianLSList = map.GetPedestrianLSList();

            if (pedestrianSFList.empty() || pedestrianLSList.empty()) return;

            //Comprueba si hay un peaton adyacente iterando en ambas listas
            for (int i = 0; i < pedestrianLSList.size(); i++)
            {
                Pedestrian & p = pedestrianLSList [ i ];
                if (map.NextToPlayer(p))
                {
                    if ( !attacked )
                    {
                        attacked = true;
                        p.SetHP ( p.GetHP ( ) - 1 );

                        std::cout << "PRINTEANDO VIDA: " << p.GetHP ( );
                    }
                    
                    if (p.GetHP() <= 0)
                    {
                        p.SetActive(false);
                        map.GetMap()[p.GetPosition().y][p.GetPosition().x] = EMPTY;
                        //system("cls");
                        map.GetMap()[p.GetPosition().y][p.GetPosition().x] = MONEY;
                        pedestrianLSList.erase(pedestrianLSList.begin() + i);
                        map.SpawnPedestrianToMap(1, pedestrianLSList, true);
                        //UpdateMapScreen(map, player);
                        player.PrintMoney();
                    }
                    continue;
                }
            }
            for (int i = 0; i < pedestrianSFList.size(); i++)
            {
                Pedestrian & p = pedestrianSFList [ i ];
                if ( map.NextToPlayer ( p ) )
                {
                    if ( !attacked )
                    {
                        attacked = true;
                        p.SetHP ( p.GetHP ( ) - 1 );
                    }

                    if (p.GetHP() <= 0)
                    {
                        p.SetActive(false);
                        map.GetMap()[p.GetPosition().y][p.GetPosition().x] = EMPTY;
                        system("cls");
                        map.GetMap()[p.GetPosition().y][p.GetPosition().x] = MONEY;
                        pedestrianSFList.erase(pedestrianSFList.begin() + i);
                        map.SpawnPedestrianToMap(1, pedestrianSFList, true);
                        UpdateMapScreen(map, player);
                        player.PrintMoney();
                    }
                    break;
                }
            }

        }
        else if (GetAsyncKeyState(VK_ESCAPE)) //Exit game
        {
            system("cls");
            std::cout << "HAS SALIDO DEL JUEGO" << std::endl;
            break;
        }

        if (player.GetHP() <= 0)
        {
            Scenes::MostrarGameOver();
        }

        //RENDER

        //FRAMERATE
        Sleep((1000 / NUM_FPS));
    }

}