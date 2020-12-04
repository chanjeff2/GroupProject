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
    friend QDebug& operator<<(QDebug &qdebug, const ITower &tower); // for debug
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

    TowerUtility *towerUtility; // keeps pointer to towerUtility to get enemies in range
    TowerLayoutManager towerLayoutManager; // manages the GUI elements related to the tower

    QTimer *timer; // timer to perform attacks at regular intervals

	// protected constructor -> prevent instantiation of ITower
	ITower(Cell* position, TowerUtility *towerUtility, TowerType towerType);

public:
	string id; // for debug
	// data member
	IAttackStrategy *attackStrategy{nullptr}; // do attack
	AuraEffect *auraEffect{nullptr}; // apply aura effect

	// destructor
    virtual ~ITower(); // virtual destructor

	// getter
    TowerType getTowerType() const; // returns type of tower
    int getDamagePerHit() const; // returns damage per hit
    float getHitPerSec() const; // returns hit per second
    int getCost() const; // returns cost of tower
    int getRange() const; // returns range of tower
    set<EnemyType> getEffectiveTowards() const; // returns the set of enemies against which this tower is effective
    set<EnemyType> getWeakTowards() const; // returns the set of enemies against which this tower is ineffective

	// setter
    void attachImageView(QGraphicsPixmapItem *imgView, QGraphicsRectItem* rangeView); // registers pointer to the tower's image to the layout manager

	// methods
    void trigger(); // set up the timer to perform attacks at regular intervals
    void attack(); // attack focused enemy/enemies
    void remove(); // destructors the tower. Called when game ends or when tower is sold

    std::set<IEnemy*> getEnemiesInRange() const; // return set of enemies in attack range

    QGraphicsRectItem* showRange(bool visibility) const; // display range indicator
};

#endif // ITOWER_H
