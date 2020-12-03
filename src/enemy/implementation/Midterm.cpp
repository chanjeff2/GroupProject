#include "Midterm.h"
#include "src/utility/GameValues.h"

Midterm::Midterm(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::Midterm)
{
    HP = 641;
    speed = 0.8;
    worth = 8;
    armor = 2;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
