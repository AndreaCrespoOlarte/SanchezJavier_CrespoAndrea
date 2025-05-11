#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Pedestrian.h"
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

private:
    void ReadFile ( );
    void InitializeMap ( );

public:
    Map ( )
    {
        ReadFile ( );
        if ( width > 0 && height > 0 )
        {
            InitializeMap ( );
        }
    }
    MapEntities ** GetMap ( ) { return map; }
    int GetWidth ( ) { return width; }
    int GetHeight ( ) { return height; }
    std::vector<Pedestrian>& GetPedestrianSFList ( ) { return pedestrianSFList; }
    std::vector<Pedestrian>& GetPedestrianLSList ( ) { return pedestrianLSList; }

    void DrawMap ( ) const;
    void DrawAllMapVisuals ( ) const;
    void DrawFieldOfView ( Player player ) const;
    void DrawMapVisuals ( const int minX , const int maxX , const int minY , const int maxY , Player player ) const;
    void SpawnPedestrianToMap ( const int pedestrianAmount , std::vector<Pedestrian> & list , const int offset , const bool LSpedestrian ) const;
    void SetPedestrianToMap ( int pedestrianAmount , std::vector<Pedestrian> & pedestrianList , int offset , bool LSpedestrian );
    bool IsValidPosition ( const Vector2 targetPos , Player * player = nullptr ) const;
    bool NextToPlayer ( Pedestrian & p ) const;
};