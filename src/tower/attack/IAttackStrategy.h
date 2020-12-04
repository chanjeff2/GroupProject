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
    ITower *tower; // ref to tower to get tower's damage per hit and strength/weaknesses
    int maxNumOfTarget = 0; // max number of targets simultaneously attcked
    set<IEnemy*> focusedEnemies; // keep track of nearby enemies
    ITargetSelectionStrategy *targetSelectionStrategy = nullptr; // strategy to select target

	// constructor
	IAttackStrategy(ITower *tower);
public:
	virtual ~IAttackStrategy();

	// setter
    void setMaxNumOfTarget(int maxNumOfTarget); // sets max targets
    void setTargetSelectionStrategy(TargetSelectionType targetSelectionType); // sets target selection strategy

	// methods
	virtual void updateFocusedEnemyInRange() = 0; // update according to attack type
	void clearAllFocus(); // clear all focus when destroy
    void attack(); // deals damage to enemy/enemies

};

#endif // IATTACKSTRATEGY_H
