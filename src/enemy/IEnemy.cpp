#include "IEnemy.h"
#include "src/utility/EnemyUtility.h"
#include "FocusManager.h"
#include <QTimer>

// constructor
IEnemy::IEnemy(EnemyUtility *enemyUtility): enemyUtility(enemyUtility), focusManager(this), modManager(this) {
//	currentPosition = GameGrid.getCell(START[0], START[1]); // put new enemy to entry
	pathToTake = PathFindingUtility.getPathStartEnd();
	pathToTake.push_front(GameGrid.getCell(START[0], START[1])); // add dummy cell for first move

	// born to move
	move();
}

// destructor
IEnemy::~IEnemy() {
	// notify all tower focusing this enemy to clear focus
	focusManager.requestUpdateFocus();

	// retrieve resource
	ResourceManager.gainResource(worth);
}

// getter
int IEnemy::getRawSpeed() const {
	return this->speed;
}

int IEnemy::getRawArmor() const {
	return this->armor;
}

bool IEnemy::getCanSlow() const {
	return this->canSlow;
}

const deque<Cell*> &IEnemy::getPathToTake() const {
	return this->pathToTake;
}

// methods
void IEnemy::move() {
	// perform move (i.e. goto next cell in pathToTake) + decrement distanceFromEnd
	...

	// notify all tower focusing this enemy to update focus if needed
	focusManager.requestUpdateFocus();

	// get ready for next move
	long timeTilNextMove = 1000/this->modManager.getActualValue(ModManager::Attribute::Speed);
	QTimer::singleShot(timeTilNextMove, this, SLOT(this->move()));
//	postDelay({move()}, 1000/speedModManager.getActualValue())
}

void IEnemy::receiveDamage(int damage) {
	int actualDamage = damage/* equation */;
	this->HP -= actualDamage;

	// check if die
	if (this->HP <= 0) {
		enemyUtility->killEnemy(this);
	}
}

