#include "NullSelection.h"
#include "src/enemy/IEnemy.h"

using namespace std;

NullSelection::NullSelection() {};

vector<IEnemy*> NullSelection::selectTarget(set<IEnemy*> enemiesInRange, set<EnemyType> effectiveTowards,
                                              set<EnemyType> weakTowards, set<IEnemy*> focusedEnemies) {
    // Select no targets
    vector<IEnemy*> selectedTarget = {nullptr};

    return selectedTarget;
}
