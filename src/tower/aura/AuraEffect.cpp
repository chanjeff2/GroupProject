#include "AuraEffect.h"
#include "src/tower/ITower.h"
#include "src/enemy/IEnemy.h"
#include "src/utility/GameValues.h"

#include <QDebug>

// constructor
AuraEffect::AuraEffect(ITower* tower, AuraType auraType) : tower(tower), auraType(auraType) {}

AuraEffect::~AuraEffect() {
	clearAllFocus();
}

AuraType AuraEffect::getAuraType() const {
	return auraType;
}

// methods
void AuraEffect::updateAuraEffect(IEnemy *enemy, bool isApply /* false for remove */) {
	enemy->focusManager.updateAuraTowerInRange(isApply, this->auraType);
	if (isApply) {
		qDebug() << "AuraEffect: attach aura to" << *enemy;
		enemy->focusManager.attachTowerAuraEffectObserver(this->tower);
	} else {
		qDebug() << "AuraEffect: remove aura from " << *enemy;
		enemy->focusManager.detachTowerAuraEffectObserver(this->tower);
	}
}

void AuraEffect::applyAuraEffectToEnemyInRangeIfNeed() {
	// get all enemies in range
	std::set<IEnemy*> enemiesInRange = tower->getEnemiesInRange();

	// loop over all enemies in range
	for(IEnemy* enemyInRange: enemiesInRange) {
		// if enemy is not affected by aura, apply aura effect
		if (auraAffectedEnemies.find(enemyInRange) == auraAffectedEnemies.end()) {
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
			updateAuraEffect(*it, false);
			it = this->auraAffectedEnemies.erase(it);
		} else {
			++it;
		}
	}
}

void AuraEffect::clearAllFocus() {
	for (auto enemy: auraAffectedEnemies) {
		updateAuraEffect(enemy, false);
	}
}
