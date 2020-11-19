#include "IEnemy.h"
#include "src/utility/EnemyUtility.h"
#include "FocusManager.h"

// constructor
IEnemy::IEnemy(): speedModManager(this), armorModManager(this) {
	currentPosition = GameGrid(.getCell(START[0], START[1]); // put new enemy to entry
	pathToTake = PathFindingUtility.getPathStartEnd();

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

// methods
void IEnemy::move() {
	// perform move (i.e. goto next cell in pathToTake) + decrement distanceFromEnd
	...

	// notify all tower focusing this enemy to update focus if needed
	focusManager.requestUpdateFocus();

	// get ready for next move
	postDelay({move()}, 1000/speedModManager.getActualValue())
}

void IEnemy::receiveDamage(int damage) {
	int actualDamage = damage/* equation */;
	this->HP -= actualDamage;

	// check if die
	if (this->HP <= 0) {
		EnemyUtility.killEnemy(this);
	}
}

