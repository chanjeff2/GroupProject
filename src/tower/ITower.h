#ifndef ITOWER_H
#define ITOWER_H

#include <set>
using namespace std;

#include <QTimer>
#include <QObject>

// forward declaration
enum class TowerType;
enum class EnemyType;
class Cell;
class IAttackStrategy;
class IAuraEffectStrategy;
class IEnemy;
class TowerUtility;

class ITower: public QObject {
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

	TowerUtility *towerUtility;

	QTimer *timer;

	// protected constructor -> prevent instantiation of ITower
	ITower(Cell* position, TowerUtility *towerUtility);

public:
	// data member
	IAttackStrategy *attackStrategy{nullptr}; // do attack
	IAuraEffectStrategy *auraEffectStrategy{nullptr}; // apply aura effect

	// destructor
	virtual ~ITower();

	// getter
	int getDamagePerHit() const;

	float getHitPerSec() const;

	int getCost() const;

	std::set<EnemyType> getEffectiveTowards() const;

	std::set<EnemyType> getWeakTowards() const;

	// methods
	std::set<IEnemy*> getEnemiesInRange() const;
};

#endif // ITOWER_H
