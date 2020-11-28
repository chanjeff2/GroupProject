#ifndef MIDTERM_H
#define MIDTERM_H

#include "src/enemy/IEnemy.h"

class Midterm : public IEnemy
{
public:
    Midterm(EnemyUtility *enemyUtility, Path path);
};

#endif // MIDTERM_H
