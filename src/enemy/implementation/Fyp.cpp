#include "Fyp.h"
#include "src/utility/GameValues.h"

FYP::FYP(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::FYP)
{
    HP = 2250;
    speed = 1.1;
    worth = 25;
    armor = 7;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
