#include "src/utility/GameValues.h"
#include "FocusManager.h"
#include "IEnemy.h"
#include "src/tower/ITower.h"
#include "src/utility/tower/TowerUtility.h"
#include "src/tower/attack/IAttackStrategy.h"
#include "src/tower/aura/AuraEffect.h"

// constructor
FocusManager::FocusManager(IEnemy *enemy): enemy(enemy) {}

// attack focus
void FocusManager::attachTowerAttackObserver(ITower *tower) {
	towersAttacking.insert(tower);
}

void FocusManager::detachTowerAttackObserver(ITower *tower) {
	towersAttacking.erase(tower);
}

// aura effect focus
void FocusManager::attachTowerAuraEffectObserver(ITower *tower) {
	towersApplyingAura.insert(tower);
}

void FocusManager::detachTowerAuraEffectObserver(ITower *tower) {
	towersApplyingAura.erase(tower);
}

void FocusManager::updateAuraTowerInRange(bool isApply, AuraType modType) {
	if (isApply) { // applying aura effect
		switch (modType) {
			case AuraType::SlowAura: {
				// apply effect if not yet
				if (slowTowerInRange == 0)
					this->enemy->modManager.addModifier(modType);

				// increment slow tower in range
				slowTowerInRange++;
				break;
			}
			case AuraType::ArmorPierceAura: {
				// apply effect if not yet
				if (armorPiercingTowerInRange == 0)
					this->enemy->modManager.addModifier(modType);

				// increment armor piercing tower in range
				armorPiercingTowerInRange++;
				break;
			}
			case AuraType::RageAura: {
				// apply effect if not yet
				if (rageTowerInRange == 0)
					this->enemy->modManager.addModifier(modType);

				// increment rage tower in range
				rageTowerInRange++;
				break;
			}
			default: {
				// Null Aura
				break;
			}
		} // end of switch
	} else { // removing aura effect
		switch (modType) {
			case AuraType::SlowAura: {
				// decrement slow tower in range
				slowTowerInRange--;
				// remove effect if need
				if (slowTowerInRange == 0)
					this->enemy->modManager.removeModifier(modType);

				break;
			}
			case AuraType::ArmorPierceAura: {
				// decrement armor piercing tower in range
				armorPiercingTowerInRange--;
				// remove effect if need
				if (armorPiercingTowerInRange == 0)
					this->enemy->modManager.removeModifier(modType);

				break;
			}
			case AuraType::RageAura: {
				// decrement rage tower in range
				rageTowerInRange--;
				// remove effect if need
				if (rageTowerInRange == 0)
					this->enemy->modManager.removeModifier(modType);

				break;
			}
			default: {
				// Null Aura
				break;
			}
		} // end of switch
	}
}

void FocusManager::requestAddAuraEffectIfNeed() {
	for (ITower* tower: TowerUtility::refOfTowers) {
		tower->auraEffect->applyAuraEffectToEnemyInRangeIfNeed();
	}
}

// for both attack and aura effect
void FocusManager::requestUpdateFocus() {
	if (!towersAttacking.empty()) {
		auto tempTowerList = towersAttacking; // error occur if erase element while looping over list
		for(auto tower: tempTowerList) {
			tower->attackStrategy->updateFocusedEnemyInRange();
		}
	}
	if (!towersApplyingAura.empty()) {
		auto tempTowerList = towersApplyingAura; // // error occur if erase element while looping over list
		for(auto tower: tempTowerList) {
			tower->auraEffect->removeAuraEffectOfEnemyIfNeed();
		}
	}
}
