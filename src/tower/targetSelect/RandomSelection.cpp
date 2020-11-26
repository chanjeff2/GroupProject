#include "RandomSelection.h"
#include "src/enemy/IEnemy.h"
#include <random>
using namespace std;

RandomSelection::RandomSelection() {};

vector<IEnemy*> RandomSelection::selectTarget(set<IEnemy*> enemiesInRange, set<EnemyType> effectiveTowards,
											  set<EnemyType> weakTowards, set<IEnemy*> focusedEnemies) {
	// remove enemy that weak towards
	remove_if(enemiesInRange.begin(), enemiesInRange.end(), [&](IEnemy *enemy) {
		// exist in weakTowards
		return weakTowards.find(enemy->getEnemyType()) != weakTowards.end();
	});

	vector<IEnemy*> selectedTarget;
	// remove focused enemy
	set_difference(enemiesInRange.begin(), enemiesInRange.end(), focusedEnemies.begin(), focusedEnemies.end(), selectedTarget.begin());

	// randomize
	shuffle(selectedTarget.begin(), selectedTarget.end(), default_random_engine());

	return selectedTarget;
}
