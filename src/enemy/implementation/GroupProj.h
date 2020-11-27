#ifndef GROUPPROJ_H
#define GROUPPROJ_H

#include "src/enemy/IEnemy.h"

class GroupProj : public IEnemy
{
public:
    GroupProj(EnemyUtility *enemyUtility, Path path);
};

#endif // GROUPPROJ_H
