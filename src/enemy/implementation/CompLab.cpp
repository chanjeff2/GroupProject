#include "CompLab.h"
#include "src/utility/GameValues.h"

COMPLab::COMPLab(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::COMPLab)
{
	HP = 75;
	speed = 1.5;
	worth = 1;
	armor = 0;
	canSlow = true;
	canPierceArmor = true;
	canEnrage = false;

	trigger();
}
