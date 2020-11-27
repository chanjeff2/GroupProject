#ifndef DESMOND_H
#define DESMOND_H

#include "src/enemy/IEnemy.h"

class Desmond : public IEnemy
{
public:
    Desmond(EnemyUtility *enemyUtility, Path path);
};

#endif // DESMOND_H
