#ifndef NORMALATTACK_H
#define NORMALATTACK_H

#include "IAttackStrategy.h"

class NormalAttack: public IAttackStrategy {
public:
	NormalAttack(ITower *tower);
	void updateFocusedEnemyInRange();
};

#endif // NORMALATTACK_H
