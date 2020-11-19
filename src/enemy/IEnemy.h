#ifndef IENEMY_H
#define IENEMY_H

#include <vector>
using namespace std;

#include "src/map/cell.h"
#include "src/utility/GameValues.h"
#include "FocusManager.h"
#include "src/utility/EnemyUtility.h"
#include "ModManager.h"

class IEnemy {
protected:
	// data member
	EnemyType enemyType; // identify type of enemies, starting from 100
	int HP;
	float speed; // grid per sec
	int worth; // How much does the enemy worth
	int armor; // Armor points
	bool canSlow; // Immunity to slowness
	Cell *currentPosition;
	vector<Cell*> pathToTake; // linked list of cells follow the sequence of path to take to reach the end
	int distanceFromEnd;

	// protected constructor to prevent direct instantiation
	IEnemy();

	// methods
	void move();

public:
	// data member
	FocusManager focusManager; // manage tower focus
	ModManager modManager; // manage speed and armor modifiers

	// destructor
	virtual ~IEnemy();

	// getter
	int getRawSpeed() const;
	int getRawArmor() const;
	bool getCanSlow() const;

	// methods
	void receiveDamage(int damage);

	virtual void special() = 0;
	virtual void comeToDeadline() = 0;
};

#endif // IENEMY_H
