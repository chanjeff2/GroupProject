#ifndef IATTACKSTRATEGY_H
#define IATTACKSTRATEGY_H

#include <set>
using namespace std;

// forward declaration
class ITower;
class IEnemy;
class ITargetSelectionStrategy;
enum class TargetSelectionType;

class IAttackStrategy
{
protected:
	// data member
	const ITower *tower; // ref to tower
	int maxNumOfTarget = 0; // only applicable to normal attack
	set<IEnemy*> focusedEnemies;
	ITargetSelectionStrategy *targetSelectionStrategy = nullptr; // ways to select target

	// constructor
	IAttackStrategy(ITower *tower);
public:
	virtual ~IAttackStrategy();

	// setter
	void setMaxNumOfTarget(int maxNumOfTarget);

	void setTargetSelectionStrategy(TargetSelectionType targetSelectionType);

	// methods
	virtual void updateFocusedEnemyInRange() = 0; // update according to attack type

	void attack();
};

#endif // IATTACKSTRATEGY_H
