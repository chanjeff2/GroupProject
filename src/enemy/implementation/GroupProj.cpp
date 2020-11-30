#include "GroupProj.h"
#include "src/utility/GameValues.h"

GroupProj::GroupProj(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::GroupProj)
{
    HP = 50;
    speed = 1.7;
    worth = 1;
    armor = 0;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;

	trigger();
}
