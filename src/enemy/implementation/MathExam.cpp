#include "MathExam.h"
#include "src/utility/GameValues.h"

MATHExam::MATHExam(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::MATHExam)
{
    HP = 900;
    speed = 1.2;
    worth = 12;
    armor = 4;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
