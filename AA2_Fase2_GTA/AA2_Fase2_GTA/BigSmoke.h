#pragma once

#include "Vector2.h"

class BigSmoke {
private:
    Vector2 position;
    int health;
    int attackPower;

public:
    BigSmoke(Vector2 pos, int hp = 200, int attack = 50);

    Vector2 GetPosition() const;
    void SetPosition(Vector2 newPos);

    int GetHealth() const;
    void TakeDamage(int amount);
    bool IsDead() const;

    int GetAttackPower() const;
};
