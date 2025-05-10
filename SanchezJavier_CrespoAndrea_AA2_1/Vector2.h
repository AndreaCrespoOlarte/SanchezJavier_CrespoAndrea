#pragma once
struct Vector2
{
	int x;
	int y;

public:
	bool operator==(const Vector2& other) const
	{
		return x == other.x && y == other.y;
	}
	bool operator!=(const Vector2& other) const
	{
		return x != other.x && y != other.y;
	}
	bool operator < (const Vector2& other) const
	{
		return x < other.x && y < other.y;
	}
	bool operator > (const Vector2& other) const
	{
		return x > other.x && y > other.y;
	}
	bool operator <= (const Vector2& other) const
	{
		return x <= other.x && y <= other.y;
	}
	bool operator >= (const Vector2& other) const
	{
		return x >= other.x && y >= other.y;
	}
};