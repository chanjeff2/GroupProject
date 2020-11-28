#include "NormalHW.h"
#include "src/utility/GameValues.h"

NormalHW::NormalHW(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::NormalHW) {
<<<<<<< HEAD:src/enemy/NormalHW.cpp
	HP = 2;
	speed = 0.5;
	worth = 1;
	armor = 0;
=======
    HP = 56;
    speed = 1.5;
    worth = 1;
    armor = 0;
>>>>>>> dev:src/enemy/implementation/NormalHW.cpp
	canSlow = true;
	canPierceArmor = true;
	canEnrage = false;
}
