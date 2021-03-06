#include "PopQuiz.h"
#include "src/utility/GameValues.h"

PopQuiz::PopQuiz(EnemyUtility *enemyUtility, Path path) : IEnemy(enemyUtility, path, EnemyType::PopQuiz)
{
    HP = 31;
    speed = 4;
    worth = 1;
    armor = 0;
    canSlow = true;
    canPierceArmor = true;
    canEnrage = false;
}
