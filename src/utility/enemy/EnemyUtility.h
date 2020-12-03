#ifndef ENEMYUTILITY_H
#define ENEMYUTILITY_H

#include <set>
using namespace std;

// forward declaration
class IEnemy;
enum class EnemyType;
class GameGrid;

class EnemyUtility
{
	int enemyID_index{0}; // debug
public:
	enum class KillStatus {
		DieOfAttack, DieOfDeadline, Reset
	};

    set<IEnemy*> enemies; // all enemies
	GameGrid *gameGrid; // ref to game grid

	EnemyUtility(GameGrid *gameGrid);
    ~EnemyUtility();

    void generateEnemy(EnemyType enemyType);
	void killEnemy(IEnemy* enemy, KillStatus killStatus);
    void killAllEnemies();
};

#endif // ENEMYUTILITY_H
