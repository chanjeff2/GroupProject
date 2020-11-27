#include "EncryptedHW.h"
#include "src/utility/GameValues.h"

EncryptedHW::EncryptedHW(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::EncryptedHW)
{
    HP = 2;
    speed = 0.5;
    worth = 1;
    armor = 0;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;

}
