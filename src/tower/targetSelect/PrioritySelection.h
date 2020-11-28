#ifndef PRIORITYSELECTION_H
#define PRIORITYSELECTION_H

#include "ITargetSelectionStrategy.h"

class PrioritySelection: public ITargetSelectionStrategy {
public:
    PrioritySelection();
    vector<IEnemy*> selectTarget(set<IEnemy*> enemiesInRange, set<EnemyType> effectiveTowards,
                                         set<EnemyType> weakTowards, set<IEnemy*> focusedEnemies = set<IEnemy*>()) override;
};

#endif // PRIORITYSELECTION_H
