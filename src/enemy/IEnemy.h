#ifndef IENEMY_H
#define IENEMY_H

#include <deque>
using namespace std;

#include <QObject>
#include <QTimer>

#include "FocusManager.h"
#include "ModManager.h"
#include "EnemyLayoutManager.h"
#include "src/utility/pathfinding/Path.h"

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
	bool canPierceArmor;
	bool canEnrage;
	Path path; // any thing related to path
	EnemyUtility *enemyUtility; // keep ref to EnemyUtility to perform destroy
	EnemyLayoutManager enemyLayoutManager;

	QTimer *timer; // for timed move

	// protected constructor to prevent direct instantiation
	IEnemy(EnemyUtility *enemyUtility, Path path, EnemyType enemyType);

	// methods
	void move();

public:
	// data member
	FocusManager focusManager; // manage tower focus
	ModManager modManager; // manage speed and armor modifiers

	// destructor
	virtual ~IEnemy();

	// getter
	EnemyType getEnemyType() const;
	int getRawSpeed() const;
	int getRawArmor() const;
	bool getCanSlow() const;
	bool getCanPierceArmor() const;
	bool getCanEnrage() const;
	int getWorth() const;
	const Path &getPath() const;

	// setter
	void setPath(Path path);
	void attachImageView(QGraphicsPixmapItem *imgView);

	// methods
	void receiveDamage(int damage);
};

#endif // IENEMY_H
