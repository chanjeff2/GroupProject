#ifndef IATTACKSTRATEGY_H
#define IATTACKSTRATEGY_H

#include <set>
using namespace std;

#include "src/enemy/IEnemy.h"
#include "src/tower/targetSelect/ITargetSelectionStrategy.h"

// forward declaration
class ITower;

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

	// Target Selection Strategy Type
	enum class TargetSelectionType {
		Random, Priority, All, Null
	};

	// setter
	void setMaxNumOfTarget(int maxNumOfTarget);

	void setTargetSelectionStrategy(TargetSelectionType targetSelectionType);

	// methods
	virtual void updateFocusedEnemyInRange() = 0; // update according to attack type

	void attack();
};

#endif // IATTACKSTRATEGY_H
