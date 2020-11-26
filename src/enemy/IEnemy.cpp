#include "IEnemy.h"
#include "src/utility/EnemyUtility.h"
#include "src/map/cell.h"
#include "src/utility/GameValues.h"


// constructor
IEnemy::IEnemy(EnemyUtility *enemyUtility, Path path, EnemyType enemyType): path(path), enemyUtility(enemyUtility), enemyType(enemyType), focusManager(this), modManager(this) {
	// born to move
	// get ready for next move
	long timeTilNextMove = 1000/this->modManager.getActualValue(ModManager::Attribute::Speed);

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &IEnemy::move);
	timer->start(timeTilNextMove);
}

// destructor
IEnemy::~IEnemy() {
	// notify all tower focusing this enemy to clear focus
	focusManager.requestUpdateFocus();

	// stop moving
	timer->stop();
}

// getter
EnemyType IEnemy::getEnemyType() const {
	return this->enemyType;
}

int IEnemy::getRawSpeed() const {
	return this->speed;
}

int IEnemy::getRawArmor() const {
	return this->armor;
}

bool IEnemy::getCanSlow() const {
	return this->canSlow;
}

bool IEnemy::getCanPierceArmor() const {
	return this->canPierceArmor;
}

bool IEnemy::getCanEnrage() const {
	return this->canEnrage;
}

const Path &IEnemy::getPath() const {
	return this->path;
}

int IEnemy::getWorth() const {
	return this->worth;
}

// setter
void IEnemy::setPath(Path path) {
	this->path = path;
}

// methods
void IEnemy::move() {
	// check if reaching exit
	if (path.isNextCellEnd()) {
		enemyUtility->killEnemy(this, false);
		return;
	}

	// perform move (i.e. goto next cell in pathToTake) + decrement distanceFromEnd
	path.goToNextCell();

	// notify all tower focusing this enemy to update focus if needed
	focusManager.requestUpdateFocus();

	// get ready for next move
	long timeTilNextMove = 1000/this->modManager.getActualValue(ModManager::Attribute::Speed);
	if (timer->interval() != timeTilNextMove) {
		timer->setInterval(timeTilNextMove); // update timer interval in case there is change in speed;
	}
}

void IEnemy::receiveDamage(int damage) {
	int actualDamage = damage/* equation */;
	this->HP -= actualDamage;

	// check if die
	if (this->HP <= 0) {
		enemyUtility->killEnemy(this, true);
	}
}

