#ifndef ESSAY_H
#define ESSAY_H

#include "src/enemy/IEnemy.h"

class Essay : public IEnemy
{
public:
    Essay(EnemyUtility *enemyUtility, Path path);
};

#endif // ESSAY_H
