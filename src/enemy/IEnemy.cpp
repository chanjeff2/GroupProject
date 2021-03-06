#include "IEnemy.h"
#include "src/utility/enemy/EnemyUtility.h"
#include "src/map/cell.h"
#include "src/utility/GameValues.h"

#include <QDebug>

QDebug& operator<<(QDebug &qdebug, const IEnemy &enemy) {
	return qdebug << QString::fromStdString(enemy.id);
}

// constructor
IEnemy::IEnemy(EnemyUtility *enemyUtility, Path path, EnemyType enemyType): path(path), enemyUtility(enemyUtility), enemyType(enemyType) {

}

// destructor
IEnemy::~IEnemy() {
}

// getter
EnemyType IEnemy::getEnemyType() const {
	return this->enemyType;
}

float IEnemy::getRawSpeed() const {
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

void IEnemy::attachImageViews(GraphicsItemGroup *imgViewGroup, QGraphicsRectItem *hpBar, QGraphicsPixmapItem *imgView) {
	this->enemyLayoutManager.attachImageViews(imgViewGroup, hpBar, imgView);
	enemyLayoutManager.setMaxHP(this->HP);
}

void IEnemy::setImgPath(QString imgPath, QString imgPath_rage) {
	enemyLayoutManager.setImgPath(imgPath, imgPath_rage);
}

// methods
void IEnemy::move() {
	// do nothing if path is empty
	if (path.isEmpty()) {
		return;
	}

	// check if reaching exit
	if (path.isNextCellEnd()) {
		enemyUtility->killEnemy(this, EnemyUtility::KillStatus::DieOfDeadline);
		return;
	}

	// perform move (i.e. goto next cell in pathToTake) + decrement distanceFromEnd
	path.goToNextCell(this);

	// notify all tower focusing this enemy to update focus if needed
	focusManager.requestUpdateFocus();
	focusManager.requestAddAuraEffectIfNeed();

	// get ready for next move
	float timeTilNextMove = 1000/this->modManager.getActualValue(ModManager::Attribute::Speed);
	timeTilNextMove /= GAME_SPEED;

	// update UI
	enemyLayoutManager.moveTo(path.getNextCoordinate(), timeTilNextMove);

	if (timer->interval() != timeTilNextMove) {
		timer->setInterval(timeTilNextMove); // update timer interval in case there is change in speed;
	}
}

void IEnemy::die() {
	this->timer->stop();
	// notify all tower focusing this enemy to clear focus
	focusManager.requestUpdateFocus();
	// clear path to place safe
	this->path.clear();
	// delete
	this->deleteLater();
}

void IEnemy::trigger() {
	// born to move
	// get ready for next move
    float timeTilNextMove = 1000/this->modManager.getActualValue(ModManager::Attribute::Speed);
    timeTilNextMove /= GAME_SPEED;

	// update UI
    enemyLayoutManager.moveTo(path.getCurrentCoordinate());
    enemyLayoutManager.moveTo(path.getNextCoordinate(), timeTilNextMove);

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &IEnemy::move);
	timer->start(timeTilNextMove);
}

void IEnemy::toggleRage(bool isRage) {
	enemyLayoutManager.toggleRage(isRage);
}

void IEnemy::receiveDamage(int damage) {
    int actualDamage = damage - modManager.getActualValue(ModManager::Attribute::Armor);/* equation */
    if (actualDamage < 0) {
        actualDamage = 0;
    }
	this->HP -= actualDamage;

	// check if die
	if (this->HP <= 0) {
		enemyUtility->killEnemy(this, EnemyUtility::KillStatus::DieOfAttack);
	} else {
		enemyLayoutManager.setHP(HP);
	}
}

void IEnemy::speedUp() {
    this->speed = 50.0;
}
