#ifndef RANDOMSELECTION_H
#define RANDOMSELECTION_H

#include "ITargetSelectionStrategy.h"

class RandomSelection: public ITargetSelectionStrategy {
public:
	RandomSelection();
	vector<IEnemy*> selectTarget(set<IEnemy*> enemiesInRange, set<EnemyType> effectiveTowards,
										 set<EnemyType> weakTowards, set<IEnemy*> focusedEnemies = set<IEnemy*>()) override;
};

#endif // RANDOMSELECTION_H
