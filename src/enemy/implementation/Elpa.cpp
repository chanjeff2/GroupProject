#include "Elpa.h"
#include "src/utility/GameValues.h"

ELPA::ELPA(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::ELPA)
{
	HP = 175;
	speed = 1.3;
	worth = 3;
	armor = 4;
	canSlow = true;
	canPierceArmor = true;
	canEnrage = false;

	trigger();
}
