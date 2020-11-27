#include "Midterm.h"

Midterm::Midterm(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::Midterm)
{
    HP = 4;
    speed = 0.5;
    worth = 3;
    armor = 2;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
