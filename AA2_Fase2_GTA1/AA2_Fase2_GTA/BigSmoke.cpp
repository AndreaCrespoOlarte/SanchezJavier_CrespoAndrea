#include "BigSmoke.h"

BigSmoke::BigSmoke(Vector2 pos, int hp, int attack)
    : position(pos), health(hp), attackPower(attack) {
}

Vector2 BigSmoke::GetPosition() const {
    return position;
}

void BigSmoke::SetPosition(Vector2 newPos) {
    position = newPos;
}

int BigSmoke::GetHealth() const {
    return health;
}

void BigSmoke::TakeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

bool BigSmoke::IsDead() const {
    return health <= 0;
}

int BigSmoke::GetAttackPower() const {
    return attackPower;
}
