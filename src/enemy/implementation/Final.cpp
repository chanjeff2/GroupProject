#include "Final.h"
#include "src/utility/GameValues.h"

Final::Final(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::Final)
{
    HP = 1350;
    speed = 1.1;
    worth = 20;
    armor = 4;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = true;
};
