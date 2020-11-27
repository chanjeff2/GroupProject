#ifndef ITARGETSELECTIONSTRATEGY_H
#define ITARGETSELECTIONSTRATEGY_H

#include <set>
#include <vector>
using namespace std;

// forward declaration
class IEnemy;
enum class EnemyType;

class ITargetSelectionStrategy
{
public:
	ITargetSelectionStrategy();
	virtual ~ITargetSelectionStrategy();
	/**
	 * @brief selectTarget - filter away all weakTowards and focused enemies
	 * @param enemiesInRange
	 * @param effectiveTowards
	 * @param weakTowards
	 * @param focusedEnemies
	 * @return all enemies wherein [0] has the high attack priority, excluding all weakTowards and focused enemies
	 */
	virtual vector<IEnemy*> selectTarget(set<IEnemy*> enemiesInRange, set<EnemyType> effectiveTowards,
										 set<EnemyType> weakTowards, set<IEnemy*> focusedEnemies = set<IEnemy*>()) = 0;
};

#endif // ITARGETSELECTIONSTRATEGY_H
