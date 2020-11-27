#ifndef POPQUIZ_H
#define POPQUIZ_H

#include "src/enemy/IEnemy.h"

class PopQuiz : public IEnemy
{
public:
    PopQuiz(EnemyUtility *enemyUtility, Path path);
};

#endif // POPQUIZ_H
