#include "MathExam.h"
#include "src/utility/GameValues.h"

MATHExam::MATHExam(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::MATHExam)
{
    HP = 5;
    speed = 0.5;
    worth = 3;
    armor = 2;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
