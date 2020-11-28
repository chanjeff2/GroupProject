#include "Essay.h"
#include "src/utility/GameValues.h"

Essay::Essay(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::Essay) {
    HP = 144;
    speed = 1.5;
    worth = 1;
    armor = 2;
    canSlow = true;
    canPierceArmor = false;
    canEnrage = false;
}
