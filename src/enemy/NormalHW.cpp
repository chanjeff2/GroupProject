#include "NormalHW.h"
#include "src/utility/GameValues.h"

NormalHW::NormalHW(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::NormalHW) {
	HP = 2;
	speed = 0.5;
	worth = 1;
	armor = 0;
	canSlow = true;
	canPierceArmor = true;
}
