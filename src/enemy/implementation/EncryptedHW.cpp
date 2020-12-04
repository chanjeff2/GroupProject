#include "EncryptedHW.h"
#include "src/utility/GameValues.h"

EncryptedHW::EncryptedHW(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::EncryptedHW)
{
    HP = 72;
    speed = 1.5;
    worth = 1;
    armor = 0;
    canSlow = false;
    canPierceArmor = true;
    canEnrage = false;
}
