#pragma once
#include "Vector2.h"
#include <math.h>
#include "Map.h"
struct Mathf
{
	static float Distance(const Vector2& a, const Vector2& b)
	{
		return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
	}
	static float f_Distance(float a, float b)
	{
		return b > a ? b - a: a - b;
	}

	static bool DetectedCollisionAt ( const Vector2& a, const Vector2& b )
	{
		if ( a == b ) return true;
		return false;
	}/*
	static bool DetectedCollisionAt ( const Vector2 & a , Map map)
	{
		if ( map.GetMap()[a.x][ a.y] != EMPTY) return false;
			return true;
	}*/
};