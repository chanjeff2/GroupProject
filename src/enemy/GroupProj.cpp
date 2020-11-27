#include "GroupProj.h"

GroupProj::GroupProj(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::GroupProj)
{
    HP = 1;
    speed = 0.5;
    worth = 1;
    armor = 1;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
