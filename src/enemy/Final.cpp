#include "Final.h"
#include "src/utility/GameValues.h"

Final::Final(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::Final)
{
    HP = 5;
    speed = 0.5;
    worth = 3;
    armor = 3;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
};
