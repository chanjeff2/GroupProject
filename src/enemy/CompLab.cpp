#include "CompLab.h"
#include "src/utility/GameValues.h"

CompLab::CompLab(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::CompLab)
{
    HP = 2;
    speed = 0.5;
    worth = 1;
    armor = 0;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
