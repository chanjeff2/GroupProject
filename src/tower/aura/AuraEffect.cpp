#include "AuraEffect.h"
#include "src/tower/ITower.h"
#include "src/enemy/IEnemy.h"
#include "src/utility/GameValues.h"

// constructor
AuraEffect::AuraEffect(ITower* tower, AuraType auraType) : tower(tower), auraType(auraType) {}

AuraType AuraEffect::getAuraType() const {
	return auraType;
}

// methods
void AuraEffect::updateAuraEffect(IEnemy *enemy, bool isApply) {
	enemy->focusManager.updateAuraTowerInRange(isApply, this->auraType);
}

void AuraEffect::applyAuraEffectToEnemyInRangeIfNeed() {
	// get all enemies in range
	std::set<IEnemy*> enemiesInRange = tower->getEnemiesInRange();

	// loop over all enemies in range
	for(IEnemy* enemyInRange: enemiesInRange) {
		// if enemy is not affected by aura, apply aura effect
		if (auraAffectedEnemies.find(enemyInRange) == auraAffectedEnemies.end()) {
			enemyInRange->focusManager.attachTowerAuraEffectObserver(this->tower);
			updateAuraEffect(enemyInRange, true);
			this->auraAffectedEnemies.insert(enemyInRange);
		}
	}
}

void AuraEffect::removeAuraEffectOfEnemyIfNeed() {
	// get all enemies in range
	set<IEnemy*> enemiesInRange = tower->getEnemiesInRange();

	// loop over all aura affected enemies
	for(auto it = this->auraAffectedEnemies.begin(); it != this->auraAffectedEnemies.end(); /*don't add thing here*/) {
		// if enemy is not in range/ died, clear foucs
		if (enemiesInRange.find(*it) == enemiesInRange.end()) {
			(*it)->focusManager.detachTowerAuraEffectObserver(this->tower);
			updateAuraEffect(*it, false);
			it = this->auraAffectedEnemies.erase(it);
		} else {
			++it;
		}
	}
}
