#include <windows.h>
#include "Player.h"
#include "Header.h"
void Player::Move( Vector2 newPos, Map & map )
{
    position = IsValidPosition(position, map) ? newPos : position;
}