#ifndef NULLSELECTION_H
#define NULLSELECTION_H

#include "ITargetSelectionStrategy.h"

class NullSelection: public ITargetSelectionStrategy {
public:
    NullSelection();
    vector<IEnemy*> selectTarget(set<IEnemy*> enemiesInRange, set<EnemyType> effectiveTowards,
                                         set<EnemyType> weakTowards, set<IEnemy*> focusedEnemies = set<IEnemy*>()) override;
};

#endif // NULLSELECTION_H
