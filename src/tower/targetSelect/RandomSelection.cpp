#include "RandomSelection.h"
#include "src/enemy/IEnemy.h"
#include <random>
#include <algorithm>
using namespace std;

RandomSelection::RandomSelection() {};

vector<IEnemy*> RandomSelection::selectTarget(set<IEnemy*> enemiesInRange, set<EnemyType> effectiveTowards,
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

	// directly return empty vector if no new enemy
	if (enemiesInRange.empty()) {
		return selectedTarget;
	}

	// remove focused enemy
	if (!focusedEnemies.empty()) {
		set_difference(enemiesInRange.begin(), enemiesInRange.end(), focusedEnemies.begin(), focusedEnemies.end(), back_inserter(selectedTarget));
	} else {
		copy(enemiesInRange.begin(), enemiesInRange.end(), back_inserter(selectedTarget));
	}

	// randomize
	shuffle(selectedTarget.begin(), selectedTarget.end(), default_random_engine());

	return selectedTarget;
}
