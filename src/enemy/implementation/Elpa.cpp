#include "Elpa.h"
#include "src/utility/GameValues.h"

ELPA::ELPA(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::ELPA)
{
    HP = 1250;
    speed = 1.4;
    worth = 12;
	armor = 4;
	canSlow = true;
	canPierceArmor = true;
	canEnrage = false;
}
