#include "AllSelection.h"
#include "src/enemy/IEnemy.h"

using namespace std;

AllSelection::AllSelection() {};

vector<IEnemy*> AllSelection::selectTarget(set<IEnemy*> enemiesInRange, set<EnemyType> effectiveTowards,
                                              set<EnemyType> weakTowards, set<IEnemy*> focusedEnemies) {
    // remove enemy that weak towards
    remove_if(enemiesInRange.begin(), enemiesInRange.end(), [&](IEnemy *enemy) {
        // exist in weakTowards
        return weakTowards.find(enemy->getEnemyType()) != weakTowards.end();
    });

    vector<IEnemy*> selectedTarget;
    // remove focused enemy
    set_difference(enemiesInRange.begin(), enemiesInRange.end(), focusedEnemies.begin(), focusedEnemies.end(), selectedTarget.begin());

    // Select all targets

    return selectedTarget;
}
