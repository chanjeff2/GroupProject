#ifndef ENEMYUTILITY_H
#define ENEMYUTILITY_H

#include <set>
using namespace std;

#include "src/enemy/IEnemy.h"

// forward declaration
//class IEnemy;
//enum class EnemyType;
class GameGrid;

class EnemyUtility
{
public:
    set<IEnemy*> enemies; // all enemies
	GameGrid *gameGrid; // ref to game grid

	EnemyUtility(GameGrid *gameGrid);
    ~EnemyUtility();

    void generateEnemy(EnemyType enemyType);
	void killEnemy(IEnemy* enemy, bool isDieOfAttack);
};

#endif // ENEMYUTILITY_H
