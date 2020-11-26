#ifndef IAURAEFFECTSTRATEGY_H
#define IAURAEFFECTSTRATEGY_H

#include <set>
using namespace std;

// forward declaration
class ITower;
class IEnemy;
enum class AuraType;

class IAuraEffectStrategy
{
protected:
	// data member
	ITower* tower;
	set<IEnemy*> auraAffectedEnemies;
	AuraType auraType;

	// methods
	virtual void updateAuraEffect(IEnemy *enemy, bool isApply) = 0; // to be overrided

	// constructor
	IAuraEffectStrategy(ITower* tower, AuraType auraType);
public:
	virtual ~IAuraEffectStrategy() {}

	AuraType getAuraType() const;

	// methods
	void applyAuraEffectToEnemyInRangeIfNeed();

	void removeAuraEffectOfEnemyIfNeed();
};

#endif // IAURAEFFECTSTRATEGY_H
