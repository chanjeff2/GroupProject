#include "MathExam.h"
#include "src/utility/GameValues.h"

MathExam::MathExam(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::MathExam)
{
    HP = 5;
    speed = 0.5;
    worth = 3;
    armor = 2;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
