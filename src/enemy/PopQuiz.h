#ifndef POPQUIZ_H
#define POPQUIZ_H

#include "IEnemy.h"

class PopQuiz : public IEnemy
{
public:
    PopQuiz(EnemyUtility *enemyUtility, Path path);
};

#endif // POPQUIZ_H
