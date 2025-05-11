#include "Map.h"
void Map::ReadFile ( ) //Lectura de la información del archivo
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
        //Aplicamos la información del archivo al string 
        int value = std::stoi ( line ); //Casteamos los datos del string a un valor númerico
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
    SetPedestrianToMap ( pedestrianLS_Amount , pedestrianLSList , width / 3 , true );
    SetPedestrianToMap ( pedestrianSF_Amount , pedestrianSFList , width / 2 + 15 , false );
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
void Map::DrawFieldOfView ( Player player ) const //Asigna los bordes del campo de visión del jugador
{
    Vector2 pos = player.GetPosition ( );

    int minX = pos.x - FOV_X;
    int maxX = pos.x + FOV_X;

    int minY = pos.y - FOV_Y;
    int maxY = pos.y + FOV_Y;
    DrawMapVisuals ( minX , maxX , minY , maxY , player );
}

void Map::DrawMapVisuals ( const int minX , const int maxX , const int minY , const int maxY , Player player ) const
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
void Map::SpawnPedestrianToMap ( const int pedestrianAmount , std::vector<Pedestrian> & list , const int offset , const bool LSpedestrian ) const
    //Genera los peatones
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
void Map::SetPedestrianToMap ( int pedestrianAmount , std::vector<Pedestrian> & pedestrianList , int offset , bool LSpedestrian )
{
    //Coloca a los peatones en el mapa
    SpawnPedestrianToMap ( pedestrianAmount , pedestrianList , offset , LSpedestrian );
    for ( Pedestrian p : pedestrianList )
    {
        map [ p.GetPosition ( ).y ][ p.GetPosition ( ).x ] = PEDESTRIAN;
    }
} 
bool Map::IsValidPosition ( const Vector2 targetPos , Player * player) const
{
    //Comprueba si la siguiente posición es válida
    if ( targetPos.y < 0 || targetPos.y >= height - 1 || targetPos.x < 0 || targetPos.x >= width - 1 )
    {
        return false;
    }
    if ( map == nullptr )
    {
        return false;
    }

    if ( map [ targetPos.y ][ targetPos.x ] != EMPTY && map [ targetPos.y ][ targetPos.x ] != MONEY && map [ targetPos.y ][ targetPos.x ] != TAXES )
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
        /*if ( player != nullptr )
        {
            int reward = ( rand ( ) % ( moneyPerKill_LosSantos - 1 ) ) + 1;
            player->AddMoney ( reward );
        }
        map [ targetPos.y ][ targetPos.x ] = EMPTY;*/
    }

    return true;
}
bool Map::NextToPlayer ( Pedestrian & p ) const //Detectar a un jugador vecino
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
    if ( y + 1 < height && x + 1 < width && map [ y + 1 ][ x + 1 ] == PLAYER ) return true;
    if ( y + 1 < height && x - 1 >= 0 && map [ y + 1 ][ x - 1 ] == PLAYER ) return true;
    if ( y - 1 >= 0 && x + 1 < width && map [ y - 1 ][ x + 1 ] == PLAYER ) return true;
    if ( y - 1 < height && x - 1 >= 0 && map [ y - 1 ][ x - 1 ] == PLAYER ) return true;
    return false;
}

