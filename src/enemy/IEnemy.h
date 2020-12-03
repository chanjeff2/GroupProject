#ifndef IENEMY_H
#define IENEMY_H

#include <deque>
#include <string>
using namespace std;

#include <QObject>
#include <QTimer>

#include "FocusManager.h"
#include "ModManager.h"
#include "EnemyLayoutManager.h"
#include "src/utility/pathfinding/Path.h"

#include "src/main/GraphicsItemGroup.h"

// forward declaration
class Cell;
enum class EnemyType;
class EnemyUtility;

class IEnemy: public QObject {
	friend QDebug& operator<<(QDebug &qdebug, const IEnemy &enemy);
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
	string id; // for debug
	// data member
	FocusManager focusManager{this}; // manage tower focus
	ModManager modManager{this}; // manage speed and armor modifiers

	// destructor
	virtual ~IEnemy();

	// getter
	EnemyType getEnemyType() const;
	float getRawSpeed() const;
	int getRawArmor() const;
	bool getCanSlow() const;
	bool getCanPierceArmor() const;
	bool getCanEnrage() const;
	int getWorth() const;
	const Path &getPath() const;

	// setter
	void setPath(Path path);
	void attachImageViews(GraphicsItemGroup *imgViewGroup, QGraphicsRectItem *hpBar, QGraphicsPixmapItem *imgView);
	void setImgPath(QString imgPath, QString imgPath_rage);

	// methods
	void trigger(); // trigger after init in base class
	void toggleRage(bool isRage); // set rage status
	void receiveDamage(int damage);
    void speedUp(); // Speed up enemies after game over
};

#endif // IENEMY_H
