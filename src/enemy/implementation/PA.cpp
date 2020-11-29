#include "PA.h"
#include "src/utility/GameValues.h"

PA::PA(EnemyUtility *enemyUtility, Path path) : IEnemy(enemyUtility, path, EnemyType::PA)
{
    HP = 145;
    speed = 1.5;
    worth = 1;
    armor = 3;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;

	trigger();
}
