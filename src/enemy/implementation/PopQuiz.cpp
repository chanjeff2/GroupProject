#include "PopQuiz.h"
#include "src/utility/GameValues.h"

PopQuiz::PopQuiz(EnemyUtility *enemyUtility, Path path) : IEnemy(enemyUtility, path, EnemyType::PopQuiz)
{
    HP = 50;
    speed = 3.2;
    worth = 1;
    armor = 0;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
