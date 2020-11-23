#ifndef ITOWER_H
#define ITOWER_H

#include <set>
using namespace std;

// forward declaration
enum class TowerType;
enum class EnemyType;
class Cell;
class IAttackStrategy;
class IAuraEffectStrategy;
class IEnemy;

class ITower {
protected:
	// data member
	TowerType towerType; // identify type of towers, starting from 0
	int damagePerHit;
	float hitPerSec;
	set<EnemyType> effectiveTowards;
	set<EnemyType> weakTowards;
	int cost;
	int range;
	const Cell *position; // Cell contains tower,tower hold ref to cell

	// protected constructor -> prevent instantiation of ITower
	ITower(Cell* position);

public:
	// data member
	IAttackStrategy *attackStrategy{nullptr}; // do attack
	IAuraEffectStrategy *auraEffectStrategy{nullptr}; // apply aura effect

	// destructor
	virtual ~ITower();

	// getter
	int getDamagePerHit() const;

	float getHitPerSec() const;

	std::set<EnemyType> getEffectiveTowards() const;

	std::set<EnemyType> getWeakTowards() const;

	// methods
	std::set<IEnemy*> getEnemiesInRange();
};

#endif // ITOWER_H
