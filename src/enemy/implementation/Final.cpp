#include "Final.h"
#include "src/utility/GameValues.h"

Final::Final(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::Final)
{
    HP = 1280;
    speed = 1.0;
    worth = 20;
    armor = 4;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = true;

	trigger();
};
