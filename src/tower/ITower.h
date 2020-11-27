#ifndef ITOWER_H
#define ITOWER_H

#include <set>
using namespace std;

#include <QTimer>
#include <QObject>

#include "src/enemy/IEnemy.h"

#include "src/utility/GameValues.h"

#include "attack/NormalAttack.h"
#include "aura/AuraEffect.h"

// forward declaration
enum class TowerType {
    Regular = 0,
    Arts = 1,
    WolframAlpha = 2,
    Hacker = 3,
    Calc = 4,
    Nerd = 5,
    Ghostwriter = 6,
    Chegg = 7
};

//enum class EnemyType;
class Cell;
class IAttackStrategy;
class AuraEffect;
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
	ITower(Cell* position, TowerUtility *towerUtility, TowerType towerType);

public:
	// data member
	IAttackStrategy *attackStrategy{nullptr}; // do attack
	AuraEffect *auraEffect{nullptr}; // apply aura effect

	// destructor
	virtual ~ITower();

	// getter
	TowerType getTowerType() const;

	int getDamagePerHit() const;

	float getHitPerSec() const;

	int getCost() const;

	std::set<EnemyType> getEffectiveTowards() const;

	std::set<EnemyType> getWeakTowards() const;

	// methods
	std::set<IEnemy*> getEnemiesInRange() const;
};

#endif // ITOWER_H
