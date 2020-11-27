#include "Fyp.h"

FYP::FYP(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::FYP)
{
    HP = 10;
    speed = 0.5;
    worth = 10;
    armor = 7;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
