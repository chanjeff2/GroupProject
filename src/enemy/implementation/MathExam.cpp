#include "MathExam.h"
#include "src/utility/GameValues.h"

MATHExam::MATHExam(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::MATHExam)
{
    HP = 825;
    speed = 1.2;
    worth = 10;
    armor = 2;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
