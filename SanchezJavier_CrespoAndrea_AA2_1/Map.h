#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Pedestrian.h"
#include "Mathf.h"
#include "Player.h"

/*
Lectura y carga de un archivo para redimensionar el mapa.
Archivo .txt
Ancho; Alto;
Cantidad_Peatones_LosSantos; DineroPeaje_SanFierro; DineroPorKill_LosSantos;
Cantidad_Peatones_SanFierro; DineroPeaje_LasVenturas; DineroPorKill_SanFierro;

El mapa constará de 3 partes horizontales:
- Los Santos
- San Fierro
- Las Venturas

SIMBOLOS:
Paredes = X
*/
#define FOV_X 20
#define FOV_Y 20
enum MapEntities
{
    WALL = 1 ,
    EMPTY ,
    TAXES ,
    PLAYER ,
    PEDESTRIAN ,
    CAR ,
    BIG_SMOKE ,
    MONEY
};

class Map
{
    const char WALL_SYMBOL = 'X';
    const char EMPTY_SYMBOL = ' ';
    const char PEDESTRIAN_SYMBOL = 'P';
    const char CAR_SYMBOL = 'C';
    const char BIG_SMOKE_SYMBOL = 'B';
    const char MONEY_SYMBOL = '$';

    MapEntities ** map = nullptr;
    std::vector<Pedestrian> pedestrianSFList;
    std::vector<Pedestrian> pedestrianLSList;

    int width = 0;

    int height = 0;

    int pedestrianSF_Amount;
    int moneyTaxFor_SanFierro;
    int moneyPerKill_SanFierro;
    int pedestrianLS_Amount;
    int moneyPerKill_LosSantos;
    int moneyTaxFor_LasVenturas;
    int moneyPerKill_LasVenturas;

public:
    MapEntities ** GetMap ( ) { return map; }
    int GetWidth ( ) { return width; }
    int GetHeight ( ) { return height; }
    std::vector<Pedestrian>& GetPedestrianSFList ( ) { return pedestrianSFList; }
    std::vector<Pedestrian>& GetPedestrianLSList ( ) { return pedestrianLSList; }

    Map ( )
    {
        ReadFile ( );
        if ( width > 0 && height > 0 )
        {
            InitializeMap ( );
        }
    }
private:

    void ReadFile ( )
    {
        std::ifstream file ( "Board.txt" );
        if ( !file.is_open ( ) )
        {
            std::cerr << "No se pudo abrir el archivo." << std::endl;
            return;
        }

        int counter = 0;
        std::string line;
        while ( getline ( file , line , ';' ) )
        {
            int value = std::stoi ( line );
            switch ( counter )
            {
                case 0: width = value * 3; break; // Multiplicamos por 3 porque son 3 zonas horizontales
                case 1: height = value; break;
                case 2: pedestrianLS_Amount = value; break;
                case 3: moneyTaxFor_SanFierro = value; break;
                case 4: moneyPerKill_LosSantos = value; break;
                case 5: pedestrianSF_Amount = value; break;
                case 6: moneyTaxFor_LasVenturas = value; break;
                case 7: moneyPerKill_SanFierro = value; break;
                default: break;
            }
            counter++;
            if ( counter >= 8 ) break;
        }
        file.close ( );
    }

    void InitializeMap ( )
    {
        map = new MapEntities * [ height ];

        for ( int y = 0; y < height; ++y )
        {
            map [ y ] = new MapEntities [ width ];
            for ( int x = 0; x < width; ++x )
            {
                map [ y ][ x ] = EMPTY;
            }
        }

        DrawMap ( );
        SetPedestrianToMap ( pedestrianLS_Amount , pedestrianLSList , width / 3, true);
        SetPedestrianToMap ( pedestrianSF_Amount , pedestrianSFList , width / 2 + 15, false);
    }
public:

    void DrawMap ( )
    {
        if ( width == 0 || height == 0 ) return;

        int zoneWidth = width / 3;

        for ( int y = 0; y < height; ++y )
        {
            for ( int x = 0; x < width; ++x )
            {
                if ( y == 0 || x == 0 || y == height - 1 || x == width - 1 )
                {
                    map [ y ][ x ] = WALL;
                }
                else if ( x == zoneWidth || x == 2 * zoneWidth )
                {
                    if ( y >= ( height / 2 ) - 2 && y <= ( height / 2 ) + 2 )
                    {
                        map [ y ][ x ] = TAXES;
                    }
                    else
                    {
                        map [ y ][ x ] = WALL;
                    }
                }
                else
                {
                    map [ y ][ x ] = EMPTY;
                }
            }
        }
    }
    void DrawAllMapVisuals ( )
    {
        if ( width == 0 || height == 0 ) return;

        for ( int y = 0; y < height; ++y )
        {
            for ( int x = 0; x < width; ++x )
            {
                switch ( map [ y ][ x ] )
                {
                    case WALL: std::cout << WALL_SYMBOL; break;
                    case EMPTY: std::cout << EMPTY_SYMBOL; break;
                    case TAXES: std::cout << EMPTY_SYMBOL; break;
                    case PLAYER: std::cout << '^'; break;
                    case PEDESTRIAN: std::cout << PEDESTRIAN_SYMBOL; break;
                    case CAR: std::cout << CAR_SYMBOL; break;
                    case BIG_SMOKE: std::cout << BIG_SMOKE_SYMBOL; break;
                    case MONEY: std::cout << MONEY_SYMBOL; break;
                    default: std::cout << EMPTY_SYMBOL; break;
                }
            }
            std::cout << '\n';
        }
        std::cout << '\t' << '\t' << "Los_Santos" << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "San_Fierro" << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "Las_Venturas";
    }
    void DrawFieldOfView ( Player player )
    {
        Vector2 pos = player.GetPosition( );

        int minX = pos.x - FOV_X;
        int maxX = pos.x + FOV_X;

        int minY = pos.y - FOV_Y;
        int maxY = pos.y + FOV_Y;
        DrawMapVisuals ( minX , maxX , minY , maxY , player );
    }

    void DrawMapVisuals ( int minX , int maxX , int minY , int maxY , Player player )
    {
        for ( int y = minY; y <= maxY; ++y )
        {
            if ( y < 0 || y >= height ) continue;

            for ( int x = minX; x <= maxX; ++x )
            {
                if ( x < 0 || x >= width )
                {
                    std::cout << ' ';
                    continue;
                }

                switch ( map [ y ][ x ] )
                {
                    case WALL: std::cout << WALL_SYMBOL; break;
                    case EMPTY: std::cout << EMPTY_SYMBOL; break;
                    case TAXES: std::cout << EMPTY_SYMBOL; break;
                    case PLAYER: std::cout << player.GetSymbol ( ); break;
                    case PEDESTRIAN: std::cout << PEDESTRIAN_SYMBOL; break;
                    case CAR: std::cout << CAR_SYMBOL; break;
                    case BIG_SMOKE: std::cout << BIG_SMOKE_SYMBOL; break;
                    case MONEY: std::cout << MONEY_SYMBOL; break;
                    default: std::cout << '?'; break;
                }
            }

            std::cout << '\n';
        }
    }
    void SpawnPedestrianToMap ( int pedestrianAmount , std::vector<Pedestrian> & list , int offset , bool LSpedestrian )
    {
        int randX = 0;
        int randY = 0;

        // Divisiones del mapa en 3 partes
        int zoneWidth = width / 3;
        int xMin = 0;
        int xMax = 0;

        if ( LSpedestrian )
        {
            xMin = 1;
            xMax = zoneWidth - 2;
        }
        else
        {
            xMin = zoneWidth + 1;
            xMax = 2 * zoneWidth - 2;
        }

        for ( int i = 0; i < pedestrianAmount;)
        {
            int pdMoney = LSpedestrian
                ? ( rand ( ) % ( moneyPerKill_LosSantos - 1 ) ) + 1
                : ( rand ( ) % ( moneyPerKill_SanFierro - 1 ) ) + 1;

            bool occupied = false;
            Vector2 pos;
            do
            {
                randY = rand ( ) % ( height - 2 ) + 1; // y entre 1 y height-2
                randX = rand ( ) % ( xMax - xMin + 1 ) + xMin; // x entre xMin y xMax
                pos = { randX, randY };

                if ( map [ randY ][ randX ] != EMPTY )
                {
                    occupied = true;
                    continue;
                }

                for ( Pedestrian pedestrian : list )
                {
                    if ( pos == pedestrian.GetPosition ( ) )
                    {
                        occupied = true;
                        break;
                    }
                }

            }
            while ( occupied );

            Pedestrian pedestrian { pos, pdMoney };
            list.push_back ( pedestrian );
            i++;
        }
    }
    void SetPedestrianToMap ( int pedestrianAmount , std::vector<Pedestrian> & pedestrianList , int offset , bool LSpedestrian)
    {
        SpawnPedestrianToMap ( pedestrianAmount , pedestrianList , offset , LSpedestrian);
        for ( Pedestrian p : pedestrianList )
        {
            map [ p.GetPosition ( ).y ][ p.GetPosition ( ).x ] = PEDESTRIAN;
        }
    }
    bool IsValidPosition ( Vector2 targetPos , Player * player = nullptr )
    {
        if ( targetPos.y < 0 || targetPos.y >= height - 1 || targetPos.x < 0 || targetPos.x >= width - 1)
        {
            return false;
        }
        if ( map == nullptr )
        {
            return false;
        }

        if ( map [ targetPos.y ][ targetPos.x ] != EMPTY && map [ targetPos.y ][ targetPos.x ] != MONEY && map [ targetPos.y ][ targetPos.x ] )
        {
            return false;
        }

        if ( map [ targetPos.y ][ targetPos.x ] == MONEY )
        {
            if ( player != nullptr )
            {
                int reward = ( rand ( ) % ( moneyPerKill_LosSantos - 1 ) ) + 1;
                player->AddMoney ( reward );
            }
            map [ targetPos.y ][ targetPos.x ] = EMPTY;
        }
        if ( map [ targetPos.y ][ targetPos.x ] == TAXES )
        {
            if ( player != nullptr )
            {
                int reward = ( rand ( ) % ( moneyPerKill_LosSantos - 1 ) ) + 1;
                player->AddMoney ( reward );
            }
            map [ targetPos.y ][ targetPos.x ] = EMPTY;
        }

        return true;
    }
    bool NextToPlayer ( Pedestrian& p) //Detectar a un jugador vecino
    {
        int x = p.GetPosition ( ).x;
        int y = p.GetPosition ( ).y;

        if ( y < 0 || y >= height || x < 0 || x >= width )
            return false;

        if ( x + 1 < width && map [ y ][ x + 1 ] == PLAYER ) return true;
        if ( x - 1 >= 0 && map [ y ][ x - 1 ] == PLAYER ) return true;
        if ( y - 1 >= 0 && map [ y - 1 ][ x ] == PLAYER ) return true;
        if ( y + 1 < height && map [ y + 1 ][ x ] == PLAYER ) return true;
        //Checker de adyacencia diagonal
        if (y + 1 < height && x + 1 < width && map[y + 1][x + 1] == PLAYER) return true;
        if (y + 1 < height && x - 1 >= 0 && map[y + 1][x - 1] == PLAYER) return true;
        if (y - 1 >= 0 && x + 1 < width && map[y - 1][x + 1] == PLAYER) return true;
        if (y - 1 < height && x - 1 >= 0 && map[y - 1][x - 1] == PLAYER) return true;
        return false;
    }
};