#include "Desmond.h"
#include "src/utility/GameValues.h"

Desmond::Desmond(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::Desmond)
{
    HP = 750;
    speed = 2.0;
    worth = 10;
    armor = 6;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
