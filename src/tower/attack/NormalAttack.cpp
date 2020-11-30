#include "NormalAttack.h"
#include "src/tower/ITower.h"
#include "src/enemy/IEnemy.h"
#include "src/tower/targetSelect/ITargetSelectionStrategy.h"

#include <set>
#include <vector>

#include <QDebug>

using namespace std;

NormalAttack::NormalAttack(ITower *tower): IAttackStrategy(tower) {};

void NormalAttack::updateFocusedEnemyInRange() {
	// update if current focused enemies out of range/died
	set<IEnemy*> enemiesInRange = this->tower->getEnemiesInRange();

	// loop over all focused enemies
	for (auto it = this->focusedEnemies.begin(); it != this->focusedEnemies.end(); /*don't add thing here*/) {
		// remove focus if out of range/died
		if (enemiesInRange.find(*it) == enemiesInRange.end()) {
			qDebug() << "NormalAttack:" << *tower << "cancel focusing" << **it;
			// detach observer in enemy
			(*it)->focusManager.detachTowerAttackObserver(this->tower);

			it = this->focusedEnemies.erase(it);
		} else {
			++it;
		}
	}

	// no need update if no enemies in range
	if (enemiesInRange.empty()) {
		return;
	}

	int numOfFocusedEnemies = this->focusedEnemies.size();

	// add new target
	if (numOfFocusedEnemies < this->maxNumOfTarget) {
		// get vector of sorted enemies in range, where [0] should be attack first
		vector<IEnemy*> enemiesToAttack = this->targetSelectionStrategy->selectTarget(enemiesInRange, this->tower->getEffectiveTowards(), this->tower->getWeakTowards(), this->focusedEnemies);
		// update focus, keep old focus, add new focus until reach max
		if (!enemiesToAttack.empty()) {
			// loop over all sorted enemies to attack
			for (IEnemy *enemy: enemiesToAttack) {
				qDebug() << "NormalAttack:" << *tower << "focus" << *enemy;
				// add it to focus
				this->focusedEnemies.insert(enemy);
				// attach observer in enemy
				enemy->focusManager.attachTowerAttackObserver(this->tower);

				++numOfFocusedEnemies;
				// break if reach max amount of target
				if (numOfFocusedEnemies == this->maxNumOfTarget) {
					qDebug() << "NormalAttack:" << *tower << "reach max target";
					break;
				}
			}
		}
	}
}
