#ifndef NORMALHW_H
#define NORMALHW_H

#include "IEnemy.h"

class NormalHW : public IEnemy
{
public:
	NormalHW(EnemyUtility *enemyUtility, Path path);
};

#endif // NORMALHW_H
