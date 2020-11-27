#ifndef FINAL_H
#define FINAL_H

#include "IEnemy.h"

class Final : public IEnemy
{
public:
    Final(EnemyUtility *enemyUtility, Path path);
};

#endif // FINAL_H
