#include "Fyp.h"
#include "src/utility/GameValues.h"

FYP::FYP(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::FYP)
{
    HP = 2000;
    speed = 0.9;
    worth = 25;
    armor = 7;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
