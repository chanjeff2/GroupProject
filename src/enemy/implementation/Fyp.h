#ifndef FYP_H
#define FYP_H

#include "src/enemy/IEnemy.h"

class FYP : public IEnemy
{
public:
    FYP(EnemyUtility *enemyUtility, Path path);
};

#endif // FYP_H
