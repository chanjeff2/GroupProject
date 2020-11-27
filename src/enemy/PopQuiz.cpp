#include "PopQuiz.h"
#include "src/utility/GameValues.h"

PopQuiz::PopQuiz(EnemyUtility *enemyUtility, Path path) : IEnemy(enemyUtility, path, EnemyType::PopQuiz)
{
    HP = 2;
    speed = 1;
    worth = 1;
    armor = 0;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
