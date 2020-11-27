#ifndef ELPA_H
#define ELPA_H

#include "src/enemy/IEnemy.h"

class ELPA : public IEnemy
{
public:
    ELPA(EnemyUtility *enemyUtility, Path path);
};

#endif // ELPA_H
