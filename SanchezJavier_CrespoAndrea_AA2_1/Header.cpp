#include "Header.h"
#include "Map.h"
bool IsValidPosition ( Vector2 targetPos, Map& map )
{
    return map.GetMap()[targetPos.x][targetPos.y] == EMPTY;
}