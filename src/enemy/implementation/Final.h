#ifndef FINAL_H
#define FINAL_H

#include "src/enemy/IEnemy.h"

class Final : public IEnemy
{
public:
    Final(EnemyUtility *enemyUtility, Path path);
};

#endif // FINAL_H
