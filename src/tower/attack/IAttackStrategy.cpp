#include "IAttackStrategy.h"
#include "src/tower/ITower.h"

// protected constructor
IAttackStrategy::IAttackStrategy(ITower *tower): tower(tower) {}

IAttackStrategy::~IAttackStrategy() {
	delete targetSelectionStrategy;
}

// setter
void IAttackStrategy::setMaxNumOfTarget(int maxNumOfTarget) {
	this->maxNumOfTarget = maxNumOfTarget;
}

void IAttackStrategy::setTargetSelectionStrategy(TargetSelectionType targetSelectionType) {
	switch(targetSelectionType) {
//			case TargetSelectionType::Random:
//				this->targetSelectionStrategy = new RandomSelection();
//				break;
//			case TargetSelectionType::Priority:
//				this->targetSelectionStrategy = new PrioritySelection();
//				break;
//			case TargetSelectionType::All:
//				this->targetSelectionStrategy = new AllSelection();
//				break;
//			default: // just to place safe, as we set to null by default already
//				this->targetSelectionStrategy = new NullSelection();
//				break;
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
		}
	}

	// prepare for next atack
	postDelayed({
		// safe check, do nothing if this tower is deleted
		if (refOfTower.contains(this))
			attack();
	}, 1000/tower->getHitPerSec())
}
