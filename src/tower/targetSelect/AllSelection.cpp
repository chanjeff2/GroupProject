#include "AllSelection.h"
#include "src/enemy/IEnemy.h"

using namespace std;

AllSelection::AllSelection() {};

vector<IEnemy*> AllSelection::selectTarget(set<IEnemy*> enemiesInRange, set<EnemyType> effectiveTowards,
                                              set<EnemyType> weakTowards, set<IEnemy*> focusedEnemies) {
	// remove enemy that weak towards
	// erase_if hardcode
	for (auto it = enemiesInRange.begin(); it != enemiesInRange.end(); /*nothing*/) {
		// check if exist in weakTowards
		if (weakTowards.find((*it)->getEnemyType()) != weakTowards.end()) {
			it = enemiesInRange.erase(it);
		} else {
			++it;
		}
	}

    vector<IEnemy*> selectedTarget;
    // remove focused enemy
    set_difference(enemiesInRange.begin(), enemiesInRange.end(), focusedEnemies.begin(), focusedEnemies.end(), selectedTarget.begin());

    // Select all targets

    return selectedTarget;
}
