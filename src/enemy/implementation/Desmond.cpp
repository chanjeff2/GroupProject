#include "Desmond.h"
#include "src/utility/GameValues.h"

Desmond::Desmond(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::Desmond)
{
    HP = 1000;
    speed = 2.4;
    worth = 11;
	armor = 6;
	canSlow = true;
	canPierceArmor = true;
	canEnrage = true;
}
