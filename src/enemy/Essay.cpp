#include "Essay.h"
#include "src/utility/GameValues.h"

Essay::Essay(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::Essay) {
    HP = 4;
    speed = 0.5;
    worth = 2;
    armor = 1;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
