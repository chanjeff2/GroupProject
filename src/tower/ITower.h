#ifndef ITOWER_H
#define ITOWER_H

#include <set>
#include <string>
using namespace std;

#include <QTimer>
#include <QObject>
#include <QDebug>

#include "TowerLayoutManager.h"

// forward declaration
enum class TowerType;
enum class EnemyType;
class Cell;
class IAttackStrategy;
class AuraEffect;
class IEnemy;
class TowerUtility;

class ITower: public QObject {
	friend QDebug& operator<<(QDebug &qdebug, const ITower &tower);
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
	TowerLayoutManager towerLayoutManager;

	QTimer *timer;

	// protected constructor -> prevent instantiation of ITower
	ITower(Cell* position, TowerUtility *towerUtility, TowerType towerType);

public:
	string id; // for debug
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

    int getRange() const;

	set<EnemyType> getEffectiveTowards() const;

	set<EnemyType> getWeakTowards() const;

	// setter
	void attachImageView(QGraphicsPixmapItem *imgView);

	// methods
	void trigger();

	std::set<IEnemy*> getEnemiesInRange() const;
};

#endif // ITOWER_H
