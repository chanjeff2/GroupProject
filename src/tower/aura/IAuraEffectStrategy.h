#ifndef IAURAEFFECTSTRATEGY_H
#define IAURAEFFECTSTRATEGY_H

#include <set>
using namespace std;

// forward declaration
class ITower;
class IEnemy;


class IAuraEffectStrategy
{
protected:
	// data member
	ITower* tower;
	set<IEnemy*> auraAffectedEnemies;

	// methods
	virtual void updateAuraEffect(IEnemy *enemy, bool isApply) = 0; // to be overrided

	// constructor
	IAuraEffectStrategy(ITower* tower);
public:
	virtual ~IAuraEffectStrategy() {}
	// methods
	void applyAuraEffectToEnemyInRangeIfNeed();

	void removeAuraEffectOfEnemyIfNeed();
};

#endif // IAURAEFFECTSTRATEGY_H
