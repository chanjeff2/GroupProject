#include "Midterm.h"
#include "src/utility/GameValues.h"

Midterm::Midterm(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::Midterm)
{
    HP = 576;
    speed = 0.9;
    worth = 8;
    armor = 2;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;

	trigger();
}
