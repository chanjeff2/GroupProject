#include "Desmond.h"
#include "src/utility/GameValues.h"

Desmond::Desmond(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::Desmond)
{
    HP = 1125;
    speed = 2.4;
    worth = 9;
	armor = 6;
	canSlow = true;
	canPierceArmor = true;
	canEnrage = false;
}
