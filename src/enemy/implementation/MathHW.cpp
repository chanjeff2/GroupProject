#include "MathHW.h"
#include "src/utility/GameValues.h"

MathHW::MathHW(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::MathHW)
{
    HP = 60;
    speed = 1.5;
    worth = 1;
    armor = 3;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;

	trigger();
}
