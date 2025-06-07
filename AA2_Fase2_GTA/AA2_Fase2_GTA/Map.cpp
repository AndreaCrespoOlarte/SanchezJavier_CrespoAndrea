#include "Map.h"
#include "Scenes.h"
void Map::ReadFile ( ) //Lectura de la información del archivo
{
    std::ifstream file ( "config.txt" );
    if ( !file.is_open ( ) )
    {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return;
    }

    int counter = 0;
    std::string line;
    while ( getline ( file , line , ';' ) )
    {
        //Aplicamos la información del archivo al string 
        int value = std::stoi ( line ); //Casteamos los datos del string a un valor númerico
        switch ( counter )
        {
        case 0: SetWidth(value * 3); break; // Multiplicamos por 3 porque son 3 zonas horizontales
        case 1: SetHeight(value); break;

        case 2: Set_PedestrianLS_Amount(value); break;
        case 3: Set_MoneyTaxFor_SanFierro(value); break;
        case 4: Set_MoneyPerKill_LosSantos(value); break;
        case 5: Set_PedestrianLS_Health(value); break;

        case 6: Set_PedestrianSF_Amount(value); break;
        case 7: Set_MoneyTaxFor_LasVenturas(value); break;
        case 8: Set_MoneyPerKill_SanFierro(value); break;
        case 9: Set_PedestrianSF_Health(value); break;

        case 10: Set_LS_CarsAmount(value); break;
        case 11: Set_SF_CarsAmount(value); break;
        case 12: Set_LA_CarsAmount(value); break;
        default: break;
        }
        counter++;
        if ( counter >= 13 ) break;
    }
    file.close ( );
}
void Map::InitializeMap ( ) //Inicializa el array dinámico
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
    SetPedestrianToMap ( pedestrianLS_Amount , pedestrianLSList, true );
    SetPedestrianToMap ( pedestrianSF_Amount , pedestrianSFList, false );
    SetCarToMap(LS_CarsAmount,carsLS,LosSantos);
    SetCarToMap(SF_CarsAmount,carsSF,SanFierro);
    SetCarToMap(LA_CarsAmount,carsLA,LasVenturas);
    SpawnBigSmoke();
}
void Map::SpawnBigSmoke() 
{
    int zoneWidth = width / 3;
    int xMin = 2 * zoneWidth + 1;
    int xMax = width - 2;
    int x, y;

    // Buscar celda vacía
    do {
        x = (zoneWidth / 2) + (zoneWidth * 2);
        y = height / 2;
    } while (map[y][x] != EMPTY);

    Vector2 pos = { x, y };
    bigSmoke = new BigSmoke(pos, 200, 50); // Mucha vida, ataque alto
    map[y][x] = BIG_SMOKE;
}


void Map::DrawMap ( ) const //Asigna a cada celda lo que contiene
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
void Map::DrawAllMapVisuals ( ) const //Dibuja por pantalla los símbolos de cada celda
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
void Map::DrawFieldOfView ( Vector2 pos, Orientation playerOrientation) const //Asigna los bordes del campo de visión del jugador
{
    int minX = pos.x - FOV_X;
    int maxX = pos.x + FOV_X;

    int minY = pos.y - FOV_Y;
    int maxY = pos.y + FOV_Y;
    DrawMapVisuals ( minX , maxX , minY , maxY, playerOrientation);
}

void Map::DrawMapVisuals ( const int minX , const int maxX , const int minY , const int maxY , Orientation playerOrientation) const
{
    //Dibuja aquello dentro del campo de visión del jugador
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
                case PLAYER: 
                        switch (playerOrientation)
                        {
                            case NORTH:
                                std::cout << '^';
                                break;
                            case SOUTH:
                                std::cout << 'v';
                                break;
                            case EAST:
                                std::cout << '<';
                                break;
                            case WEST:
                                std::cout << '>';
                                break;
                            case ON_CAR:
                                std::cout << 'C';
                                break;
                            default:
                                break;
                        }; 
                    break;
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
void Map::SpawnPedestrianToMap ( const int pedestrianAmount , std::vector<Pedestrian> & list, const bool LSpedestrian ) const
    //Genera los peatones
{
    int randX = 0;
    int randY = 0;
    int pedestrianHP; 
    // Divisiones del mapa en 3 partes
    int zoneWidth = width / 3;
    int xMin = 0;
    int xMax = 0;

    int randBehavior = rand()%2; 
    bool behavior; 

    if ( LSpedestrian )
    {
        xMin = 1;
        xMax = zoneWidth - 2;
        pedestrianHP = pedestrianLS_Health;
    }
    else
    {
        xMin = zoneWidth + 1;
        xMax = 2 * zoneWidth - 2;
        pedestrianHP = pedestrianSF_Health;
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

        if (randBehavior == 1) behavior = true;
        else behavior = false; 
        
        Pedestrian pedestrian{ pos, pdMoney, pedestrianHP, behavior, pedestrianHP, false };
        list.push_back ( pedestrian );
        i++;
    }
}
void Map::SpawnCarsToMap ( const int carAmount , std::vector<Car> & list, Location location ) const
{
    int randX = 0;
    int randY = 0;
    // Divisiones del mapa en 3 partes
    int zoneWidth = width / 3;
    int xMin = 0;
    int xMax = 0;

    int randBehavior = rand()%1; 
    bool behavior; 
    switch (location)
    {
        case LosSantos:
            xMin = 1;
            xMax = zoneWidth - 2;
            break;
        case SanFierro:
            xMin = zoneWidth + 1;
            xMax = 2 * zoneWidth - 2;
            break;
        case LasVenturas:
            xMin = zoneWidth * 2 + 1;
            xMax = 3 * zoneWidth - 2;
            break;
        default:
            break;
    }

    for ( int i = 0; i < carAmount;)
    {
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

            for ( Car car : list )
            {
                if ( pos == car.GetPosition ( ) )
                {
                    occupied = true;
                    break;
                }
            }
        }
        while ( occupied );

        if (randBehavior == 1)
            behavior = true;
        else
            behavior = false; 
        
        Car car { pos, location};
        list.push_back ( car );
        i++;
    }
}
void Map::SetPedestrianToMap ( int pedestrianAmount , std::vector<Pedestrian> & pedestrianList, bool LSpedestrian )
{
    //Coloca a los peatones en el mapa
    SpawnPedestrianToMap ( pedestrianAmount , pedestrianList, LSpedestrian );
    for ( Pedestrian p : pedestrianList )
    {
        map [ p.GetPosition ( ).y ][ p.GetPosition ( ).x ] = PEDESTRIAN;
    }
}
void Map::SetCarToMap(int carAmount, std::vector<Car>& carList, Location location)
{
    //Coloca a los peatones en el mapa
    SpawnCarsToMap(carAmount, carList, location);
    for ( Car c : carList )
    {
        map [ c.GetPosition ( ).y ][ c.GetPosition ( ).x ] = CAR;
    }
} 
bool Map::IsValidPosition ( const Vector2 targetPos , Player * player ) const
{
    //Comprueba si la siguiente posición es válida
    if ( targetPos.y < 0 || targetPos.y >= height || targetPos.x < 0 || targetPos.x >= width )
        return false;

    if ( map == nullptr )
        return false;

    MapEntities entity = map [ targetPos.y ][ targetPos.x ];

    // Big Smoke siempre bloquea el paso
    if ( entity == MapEntities::BIG_SMOKE ) return false;
    // Si pisa impuestos
    if ( entity == MapEntities::TAXES && player != nullptr )
    {
        int penalty = moneyTaxFor_LasVenturas;
        player->AddMoney ( -penalty );
        if ( player->GetMoney ( ) < 0 )
        {
            std::cout << "Dinero insuficiente. Te han detenido los azules.";
            Scenes::MostrarGameOver ( );
        }
        map [ targetPos.y ][ targetPos.x ] = MapEntities::EMPTY;
    }
    // Si el jugador está en coche
    if ( player != nullptr && player->GetOnCar ( ) )
    {
        if ( entity == MapEntities::WALL || entity == MapEntities::CAR ) return false;
        return true;
    }

    // Si el jugador no está en coche
    if ( entity == MapEntities::EMPTY || entity == MapEntities::MONEY || entity == MapEntities::TAXES )
    {
        // Si pisa dinero
        if ( entity == MapEntities::MONEY && player != nullptr )
        {
            int reward = ( rand ( ) % ( moneyPerKill_LosSantos - 1 ) ) + 1;
            player->AddMoney ( reward );
            map [ targetPos.y ][ targetPos.x ] = MapEntities::EMPTY;
        }
        return true;
    }
    return false;
}
bool Map::NextToPlayer(Pedestrian& p, BigSmoke* bg) const
{
    Vector2 pos = p.GetPosition();

    for (int dy = pos.y - 1; dy <= pos.y + 1; dy++)
    {
        for (int dx = pos.x - 1; dx <= pos.x + 1; dx++)
        {
            if (dx == pos.x && dy == pos.y)
                continue;
            if ( bg != nullptr )
            {
                if ( dy >= 0 && dy < height && dx >= 0 && dx < width )
                {
                    if ( map [ dy ][ dx ] == PLAYER )
                    {
                        return true;
                    }
                }
            }
            if (dy >= 0 && dy < height && dx >= 0 && dx < width)
            {
                if (map[dy][dx] == PLAYER)
                {
                    return true;
                }
            }
        }
    }

    return false;
}
