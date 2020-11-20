#ifndef ENEMYUTILITY_H
#define ENEMYUTILITY_H

#include <set>
using namespace std;

#include "GameValues.h"

// forward declaration
class IEnemy;

class EnemyUtility
{
public:
    set<IEnemy*> enemies; // all enemies

        EnemyUtility();
        ~EnemyUtility();

        void generateEnemy(EnemyType enemyType);
        void killEnemy(IEnemy* enemy);
};

#endif // ENEMYUTILITY_H
