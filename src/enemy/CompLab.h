#ifndef COMPLAB_H
#define COMPLAB_H

#include "IEnemy.h"

class CompLab : public IEnemy
{
public:
    CompLab(EnemyUtility *enemyUtility, Path path);
};

#endif // COMPLAB_H
