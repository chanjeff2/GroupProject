#include "IAttackStrategy.h"
#include "src/tower/ITower.h"
#include "src/enemy/IEnemy.h"
#include "src/tower/targetSelect/ITargetSelectionStrategy.h"
#include "src/utility/GameValues.h"

#include <cmath>

#include <QDebug>

#include "src/tower/targetSelect/RandomSelection.h"
#include "src/tower/targetSelect/PrioritySelection.h"
#include "src/tower/targetSelect/AllSelection.h"
#include "src/tower/targetSelect/NullSelection.h"


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

	// return if no focus
	if (focusedEnemies.empty()) {
		return;
	}

	// perform attack if have focus
	auto tempEnemyList = focusedEnemies; // error occur if erase enemy (die) while looping over list
	for (IEnemy *focusedEnemy: tempEnemyList) {
		// attack !
		// no effective
		if (tower->getEffectiveTowards().empty()) {
			qDebug() << "IAttackStrategy:" << *tower << "attack" << *focusedEnemy
					 << "with" << tower->getDamagePerHit() << "damage";
			focusedEnemy->receiveDamage(tower->getDamagePerHit());
			continue;
		}
		// check effective
		if (tower->getEffectiveTowards().find(focusedEnemy->getEnemyType()) != tower->getEffectiveTowards().end()) {
			int damage = round(tower->getDamagePerHit() * EFFECTIVE_ATTACK_RATIO);
			qDebug() << "IAttackStrategy:" << *tower << "attack" << *focusedEnemy
					 << "with effectively" << damage << "damage";
			focusedEnemy->receiveDamage(damage);
		} else {
			qDebug() << "IAttackStrategy:" << *tower << "attack" << *focusedEnemy
					 << "with" << tower->getDamagePerHit() << "damage";
			focusedEnemy->receiveDamage(tower->getDamagePerHit());
		}
	}

}

void IAttackStrategy::clearAllFocus() {
	for (auto enemy: focusedEnemies) {
		enemy->focusManager.detachTowerAttackObserver(this->tower);
	}
}
