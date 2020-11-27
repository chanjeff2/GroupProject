#ifndef COMPLAB_H
#define COMPLAB_H

#include "src/enemy/IEnemy.h"

class COMPLab : public IEnemy
{
public:
    COMPLab(EnemyUtility *enemyUtility, Path path);
};

#endif // COMPLAB_H
