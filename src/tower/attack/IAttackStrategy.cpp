#include "IAttackStrategy.h"
#include "src/tower/ITower.h"
#include "src/enemy/IEnemy.h"
#include "src/tower/targetSelect/ITargetSelectionStrategy.h"
#include "src/utility/GameValues.h"

#include <cmath>

#include "src/tower/targetSelect/RandomSelection.h"

// protected constructor
IAttackStrategy::IAttackStrategy(ITower *tower): tower(tower) {}

IAttackStrategy::~IAttackStrategy() {
	clearAllFocus();
	delete targetSelectionStrategy;
}

// setter
void IAttackStrategy::setMaxNumOfTarget(int maxNumOfTarget) {
	this->maxNumOfTarget = maxNumOfTarget;
}

void IAttackStrategy::setTargetSelectionStrategy(TargetSelectionType targetSelectionType) {
	switch(targetSelectionType) {
			case TargetSelectionType::Random:
				this->targetSelectionStrategy = new RandomSelection();
				break;
			case TargetSelectionType::Priority:
				this->targetSelectionStrategy = new PrioritySelection();
				break;
			case TargetSelectionType::All:
				this->targetSelectionStrategy = new AllSelection();
				break;
			default: // just to place safe, as we set to null by default already
				this->targetSelectionStrategy = new NullSelection();
				break;
	}
}

// methods
void IAttackStrategy::attack() {
	// check if focused max amount of target(s) if possible
	updateFocusedEnemyInRange();

	// perform attack if have focus
	if (!focusedEnemies.empty()) {
		for (IEnemy *focusedEnemy: focusedEnemies) {
			// attack !
			if (tower->getEffectiveTowards().find(focusedEnemy->getEnemyType()) != tower->getEffectiveTowards().end()) {
				int damage = round(tower->getDamagePerHit() * EFFECTIVE_ATTACK_RATIO);
				focusedEnemy->receiveDamage(damage);
			} else {
				focusedEnemy->receiveDamage(tower->getDamagePerHit());
			}
		}
	}
}

void IAttackStrategy::clearAllFocus() {
	for (auto enemy: focusedEnemies) {
		enemy->focusManager.detachTowerAttackObserver(this->tower);
	}
}
