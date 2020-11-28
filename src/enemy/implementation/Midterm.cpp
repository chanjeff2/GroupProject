#include "Midterm.h"
#include "src/utility/GameValues.h"

Midterm::Midterm(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::Midterm)
{
    HP = 2;
    speed = 0.5;
    worth = 2;
    armor = 2;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
