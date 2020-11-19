#ifndef FOCUSMANAGER_H
#define FOCUSMANAGER_H

#include <set>
using namespace std;

#include "src/utility/GameValues.h"

// forward declaration
class IEnemy;
class ITower;
//enum class ModType;

class FocusManager
{
	IEnemy *enemy;
	set<ITower*> towersAttacking;
	set<ITower*> towersApplyingAura;
	int slowTowerInRange = 0;
	int armorPiercingTowerInRange = 0;
	int rageTowerInRange = 0;

public:
	// constructor
	FocusManager(IEnemy *enemy);

	// attack focus
	void attachTowerAttackObserver(ITower *tower);

	void detachTowerAttackObserver(ITower *tower);

	// aura effect focus
	void attachTowerAuraEffectObserver(ITower *tower);

	void detachTowerAuraEffectObserver(ITower *tower);

	void updateAuraTowerInRange(bool isApply, AuraType modType); // do ++ or --

	void requestAddAuraEffectIfNeed(); // loop through all auro tower and check if need

	// for both attack and aura effect
	void requestUpdateFocus();
};

#endif // FOCUSMANAGER_H
