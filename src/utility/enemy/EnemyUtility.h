#ifndef ENEMYUTILITY_H
#define ENEMYUTILITY_H

#include <set>
using namespace std;

#include "src/enemy/IEnemy.h"

#include "src/enemy/implementation/NormalHW.h"
#include "src/enemy/implementation/Essay.h"
#include "src/enemy/implementation/EncryptedHW.h"
#include "src/enemy/implementation/GroupProj.h"
#include "src/enemy/implementation/MathHW.h"
#include "src/enemy/implementation/CompLab.h"
#include "src/enemy/implementation/PA.h"
#include "src/enemy/implementation/Desmond.h"
#include "src/enemy/implementation/PopQuiz.h"
#include "src/enemy/implementation/Midterm.h"
#include "src/enemy/implementation/MathExam.h"
#include "src/enemy/implementation/Final.h"
#include "src/enemy/implementation/Elpa.h"
#include "src/enemy/implementation/Fyp.h"

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
