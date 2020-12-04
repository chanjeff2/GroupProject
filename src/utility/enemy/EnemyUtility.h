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
        DieOfAttack,    // killed by tower
        DieOfDeadline,  // reach the deadline
        Reset           // killed by game reset
	};

    set<IEnemy*> enemies; // ref to all enemies
	GameGrid *gameGrid; // ref to game grid

	EnemyUtility(GameGrid *gameGrid);
    ~EnemyUtility();

    void generateEnemy(EnemyType enemyType); // spawn enemy
    void killEnemy(IEnemy* enemy, KillStatus killStatus); // kill enemy
    void killAllEnemies(); // kill all enemy (for game reset)
};

#endif // ENEMYUTILITY_H
