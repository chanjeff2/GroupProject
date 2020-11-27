#include "PA.h"
#include "src/utility/GameValues.h"

PA::PA(EnemyUtility *enemyUtility, Path path) : IEnemy(enemyUtility, path, EnemyType::PA)
{
    HP = 5;
    speed = 0.5;
    worth = 5;
    armor = 3;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
