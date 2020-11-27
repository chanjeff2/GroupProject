#ifndef ELPA_H
#define ELPA_H

#include "IEnemy.h"

class ELPA : public IEnemy
{
public:
    ELPA(EnemyUtility *enemyUtility, Path path);
};

#endif // ELPA_H
