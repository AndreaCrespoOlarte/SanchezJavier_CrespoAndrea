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

enum MapEntities
{
    WALL = 1 ,
    EMPTY ,
    PLAYER ,
    PEDESTRIAN ,
    CAR ,
    BIG_SMOKE
};

class Map
{
    const char WALL_SYMBOL = 'X';
    const char EMPTY_SYMBOL = ' ';
    const char PLAYER_SYMBOL = 'P';
    const char PEDESTRIAN_SYMBOL = 'P';
    const char CAR_SYMBOL = 'C';
    const char BIG_SMOKE_SYMBOL = 'B';

    MapEntities** map;
    std::vector<Pedestrian> pedestrianSFList;
    std::vector<Pedestrian> pedestrianLSList;

    int width = 0;

    int height = 0;
    int fieldOfViewX;
    int fieldOfViewY;

    int pedestrianSF_Amount;
    int moneyTaxFor_SanFierro;
    int moneyPerKill_SanFierro;
    int pedestrianLS_Amount;
    int moneyPerKill_LosSantos;
    int moneyTaxFor_LasVenturas;
    int moneyPerKill_LasVenturas;

public:
    MapEntities** GetMap ( ) { return map; }
    int GetWidth ( ) { return width; }
    int GetHeight ( ) { return height; }
    std::vector<Pedestrian> GetPedestrianSFList ( ) { return pedestrianSFList; }
    std::vector<Pedestrian> GetPedestrianLSList ( ) { return pedestrianLSList; }

    Map ( float fovX , float fovY )
    {
        fieldOfViewX = fovX;
        fieldOfViewY = fovY;
        ReadFile ( );
        DrawMap ( );
        SetPedestrianToMap ( pedestrianSF_Amount , pedestrianSFList , width / 3 );
        SetPedestrianToMap ( pedestrianLS_Amount , pedestrianLSList , width / 2 + 15 );
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
        for ( int i = 0; i < height; i++ )
        {
            for ( int j = 0; j < width; j++ )
            {
                map [ i ][ j ] = EMPTY;
            }
        }
    }

public:

    void DrawMap ( )
    {
        if ( width == 0 || height == 0 ) return;

        int zoneWidth = width / 3;

        for ( int i = 0; i < width; i++ )
        {
            for ( int j = 0; j < height; j++ ) 
            {
                if ( i == 0 || j == 0 || i == width - 1 || j == height - 1 )
                {
                    map [ i ][ j ] = WALL;
                }
                else if ( i == zoneWidth || i == 2 * zoneWidth )
                {
                    if ( j >= ( height / 2 ) - 2 && j <= ( height / 2 ) + 2 )
                    {
                        map [ i ][ j ] = EMPTY;
                    }
                    else
                    {
                        map [ i ][ j ] = WALL;
                    }
                }
                else
                {
                    map [ i ][ j ] = EMPTY;
                }
            }
        }
    }
    void DrawAllMapVisuals ( ) //Used for testing all map features
    {
        if ( width == 0 || height == 0 ) return;
        for ( int j = 0; j < height; j++ ) // filas
        {
            for ( int i = 0; i < width; i++ ) // columnas
            {
                switch ( map [ i ][ j ] )
                {
                    case WALL: std::cout << WALL_SYMBOL; break;
                    case EMPTY: std::cout << EMPTY_SYMBOL; break;
                    case PLAYER: std::cout << PLAYER_SYMBOL; break;
                    case PEDESTRIAN: std::cout << PEDESTRIAN_SYMBOL; break;
                    case CAR: std::cout << CAR_SYMBOL; break;
                    case BIG_SMOKE: std::cout << BIG_SMOKE_SYMBOL; break;
                }
            }
            std::cout << '\n';
        }
    }

    void DrawFieldOfView ( Player player ) //FOV playable
    {
        Vector2 pos = player.GetPosition ( );
        int _width = Mathf::f_Distance ( pos.x , fieldOfViewX );
        int _height = Mathf::f_Distance ( pos.y , fieldOfViewY );
        DrawMapVisuals ( _width , _height );
    }

    void DrawMapVisuals ( int _width , int _height )
    {
        for ( int j = 0; j < _height; j++ )
        {
            for ( int i = 0; i < _width; i++ )
            {
                switch ( map [ i ][ j ] )
                {
                    case WALL: std::cout << WALL_SYMBOL; break;
                    case EMPTY: std::cout << EMPTY_SYMBOL; break;
                    case PLAYER: std::cout << PLAYER_SYMBOL; break;
                    case PEDESTRIAN: std::cout << PEDESTRIAN_SYMBOL; break;
                    case CAR: std::cout << CAR_SYMBOL; break;
                    case BIG_SMOKE: std::cout << BIG_SMOKE_SYMBOL; break;
                }
            }
            std::cout << '\n';
        }
    }

    void SpawnPedestrianToMap ( int pedestrianAmount,std::vector<Pedestrian>& list, int offset )
    {
        int randX = 0;
        int randY = 0;
        for ( int i = 0; i < pedestrianAmount;)
        {
            bool occupied = false;
            Vector2 pos;
            do
            {
                randX = rand ( ) % ( width - offset ) + 1;
                randY = rand ( ) % ( height - 2 ) + 1;
                pos = { randX, randY };

                if ( map [ randX ][ randY ] != EMPTY )
                {
                    return;
                        
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

            Pedestrian pedestrian = Pedestrian { pos };
            list.push_back ( pedestrian );
            i++;
        }
    }
    void SetPedestrianToMap ( int pedestrianAmount, std::vector<Pedestrian>& pedestrianList, int offset )
    {

        SpawnPedestrianToMap ( pedestrianAmount , pedestrianList, offset );
        for ( Pedestrian p : pedestrianList)
        {
            map [ p.GetPosition ( ).x ][ p.GetPosition ( ).y ] = PEDESTRIAN;
        }
    }
};