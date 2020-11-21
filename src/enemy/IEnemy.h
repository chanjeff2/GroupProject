#ifndef IENEMY_H
#define IENEMY_H

#include <deque>
using namespace std;

#include <QObject>

#include "FocusManager.h"
#include "ModManager.h"

// forward declaration
class Cell;
enum class EnemyType;
class EnemyUtility;

class IEnemy: public QObject {
protected:
	// data member
	EnemyType enemyType; // identify type of enemies, starting from 100
	int HP;
	float speed; // grid per sec
	int worth; // How much does the enemy worth
	int armor; // Armor points
	bool canSlow; // Immunity to slowness
//	Cell *currentPosition;
	deque<Cell*> pathToTake; // pathToTake[0] = currentPosition
	int distanceFromEnd;
	EnemyUtility *enemyUtility; // keep ref to EnemyUtility to perform destroy

	// protected constructor to prevent direct instantiation
	IEnemy(EnemyUtility *enemyUtility);

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
	const deque<Cell*> &getPathToTake() const;

	// methods
	void receiveDamage(int damage);

	virtual void special() = 0;
	virtual void comeToDeadline() = 0;
};

#endif // IENEMY_H
