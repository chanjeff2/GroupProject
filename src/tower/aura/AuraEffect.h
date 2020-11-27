#ifndef AURAEFFECT_H
#define AURAEFFECT_H

#include <set>
using namespace std;

// forward declaration
class ITower;
class IEnemy;
enum class AuraType;

class AuraEffect
{
protected:
	// data member
	ITower* tower;
	set<IEnemy*> auraAffectedEnemies;
	AuraType auraType;

	// methods
	void updateAuraEffect(IEnemy *enemy, bool isApply);
public:
	// constructor
	AuraEffect(ITower* tower, AuraType auraType);
	~AuraEffect() {}

	AuraType getAuraType() const;

	// methods
	void applyAuraEffectToEnemyInRangeIfNeed();

	void removeAuraEffectOfEnemyIfNeed();

	void clearAllFocus(); // clear all focus when destroy
};

#endif // AURAEFFECT_H
