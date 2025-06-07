#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Pedestrian.h"
#include "Player.h"
#include "Cars.h"
#include "BigSmoke.h"

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
private:
    const char WALL_SYMBOL = 'X';
    const char EMPTY_SYMBOL = ' ';
    const char PEDESTRIAN_SYMBOL = 'P';
    const char CAR_SYMBOL = 'C';
    const char BIG_SMOKE_SYMBOL = 'B';
    const char MONEY_SYMBOL = '$';

    //Campo de visión tanto en x como en y
    const int FOV_X = 20;
    const int FOV_Y = 20;

    MapEntities ** map = nullptr;
    std::vector<Pedestrian> pedestrianSFList;
    std::vector<Pedestrian> pedestrianLSList;

    int width = 0;
    int height = 0;

    int pedestrianSF_Amount;
    int moneyTaxFor_SanFierro;
    int moneyPerKill_SanFierro;
    int pedestrianSF_Health;

    int pedestrianLS_Amount;
    int moneyPerKill_LosSantos;
    int moneyTaxFor_LasVenturas;
    int moneyPerKill_LasVenturas;
    int pedestrianLS_Health;

    int LS_CarsAmount;
    int SF_CarsAmount;
    int LA_CarsAmount;
    std::vector<Car> carsLS;
    std::vector<Car> carsSF;
    std::vector<Car> carsLA;

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
    BigSmoke* bigSmoke;

    MapEntities ** GetMap ( ) { return map; }

    int GetWidth ( ) { return width; }
    int GetHeight ( ) { return height; }

    void SetWidth ( int v ) { width = v; }
    void SetHeight( int v ) { height = v; }

    void Set_PedestrianLS_Amount(int v) { pedestrianLS_Amount = v; }
    void Set_MoneyTaxFor_SanFierro(int v) { moneyTaxFor_SanFierro = v; }
    void Set_MoneyPerKill_LosSantos(int v) { moneyPerKill_LosSantos = v; }
    void Set_PedestrianLS_Health(int v) { pedestrianLS_Health = v; }

    void Set_PedestrianSF_Amount(int v) { pedestrianSF_Amount = v; }
    void Set_MoneyTaxFor_LasVenturas(int v) { moneyTaxFor_LasVenturas = v; }
    void Set_MoneyPerKill_SanFierro(int v) { moneyPerKill_SanFierro = v; }
    void Set_MoneyPerKill_LasVenturas(int v) { moneyPerKill_LasVenturas = v; }
    void Set_PedestrianSF_Health(int v) { pedestrianSF_Health = v; }

    void Set_LS_CarsAmount(int v) { LS_CarsAmount = v; }
    void Set_SF_CarsAmount(int v) { SF_CarsAmount = v; }
    void Set_LA_CarsAmount(int v) { LA_CarsAmount = v; }

    std::vector<Pedestrian>& GetPedestrianSFList ( ) { return pedestrianSFList; }
    std::vector<Pedestrian>& GetPedestrianLSList ( ) { return pedestrianLSList; }

    void DrawMap ( ) const;
    void SpawnBigSmoke();
    void DrawAllMapVisuals ( ) const;
    void DrawFieldOfView(Vector2 pos, Orientation playerOrientation) const;
    void DrawMapVisuals(const int minX, const int maxX, const int minY, const int maxY, Orientation playerOrientation) const;
    void SpawnPedestrianToMap ( const int pedestrianAmount , std::vector<Pedestrian> & list, const bool LSpedestrian ) const;
    void SpawnCarsToMap(const int carAmount, std::vector<Car>& list, Location location) const;
    void SetPedestrianToMap ( int pedestrianAmount , std::vector<Pedestrian> & pedestrianList , bool LSpedestrian );
    void SetCarToMap(int carAmount, std::vector<Car>& pedestrianList, Location location);
    bool IsValidPosition(const Vector2 targetPos, Player* player = nullptr) const;
    bool NextToPlayer ( Pedestrian & p ) const;
};