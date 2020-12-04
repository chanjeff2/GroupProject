#ifndef FOCUSMANAGER_H
#define FOCUSMANAGER_H

#include <set>
using namespace std;

// forward declaration
class IEnemy;
class ITower;
enum class AuraType;

class FocusManager
{
	IEnemy *enemy;
    set<ITower*> towersAttacking; // set of towers attacking this enemy
    set<ITower*> towersApplyingAura; // set of towers applying aura to this enemy
	int slowTowerInRange{0};
	int armorPiercingTowerInRange{0};
	int rageTowerInRange{0};

public:
	// constructor
	FocusManager(IEnemy *enemy);

	// attack focus
    void attachTowerAttackObserver(ITower *tower); // add tower to set of towers attacking
    void detachTowerAttackObserver(ITower *tower); // remove tower from set of towers attacking

	// aura effect focus
    void attachTowerAuraEffectObserver(ITower *tower); // add tower to set of towers applying aura
    void detachTowerAuraEffectObserver(ITower *tower); // remove tower from set of towers applying aura
    void updateAuraTowerInRange(bool isApply, AuraType modType); // update number of towers applying aura
    void requestAddAuraEffectIfNeed(); // loop through all towers applying aura and check if need to apply aura effect

	// for both attack and aura effect
    void requestUpdateFocus(); // update towers attacking/applying aura if move out of range
};

#endif // FOCUSMANAGER_H
