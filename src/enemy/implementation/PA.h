#ifndef PA_H
#define PA_H

#include "src/enemy/IEnemy.h"

class PA : public IEnemy
{
public:
    PA(EnemyUtility *enemyUtility, Path path);
};

#endif // PA_H
