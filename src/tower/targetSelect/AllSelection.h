#ifndef ALLSELECTION_H
#define ALLSELECTION_H

#include "ITargetSelectionStrategy.h"

class AllSelection: public ITargetSelectionStrategy {
public:
    AllSelection();
    vector<IEnemy*> selectTarget(set<IEnemy*> enemiesInRange, set<EnemyType> effectiveTowards,
                                         set<EnemyType> weakTowards, set<IEnemy*> focusedEnemies = set<IEnemy*>()) override;
};

#endif // ALLSELECTION_H
