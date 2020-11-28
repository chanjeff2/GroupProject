#ifndef MATHHW_H
#define MATHHW_H

#include "src/enemy/IEnemy.h"

class MathHW : public IEnemy
{
public:
    MathHW(EnemyUtility *enemyUtility, Path path);
};

#endif // MATHHW_H
