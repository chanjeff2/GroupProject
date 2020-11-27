#include "Desmond.h"
#include "src/utility/GameValues.h"

Desmond::Desmond(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::Desmond)
{
    HP = 7;
    speed = 0.5;
    worth = 5;
    armor = 5;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
