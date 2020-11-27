#include "MathHW.h"
#include "src/utility/GameValues.h"

MathHW::MathHW(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::MathHW)
{
    HP = 2;
    speed = 0.5;
    worth = 2;
    armor = 2;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
