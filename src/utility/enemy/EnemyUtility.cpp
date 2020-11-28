#include "EnemyUtility.h"
#include "src/utility/GameValues.h"
#include "src/enemy/IEnemy.h"
#include "src/utility/pathfinding/Path.h"
#include "src/map/GameGrid.h"

EnemyUtility::EnemyUtility(GameGrid *gameGrid): gameGrid(gameGrid) {};

EnemyUtility::~EnemyUtility() {
    for (IEnemy *enemy: enemies) {
        delete enemy;
    }
}

void EnemyUtility::generateEnemy(EnemyType enemyType) {
    // Each homework type are separate classes (to be added)
    switch(enemyType) {
        case EnemyType::NormalHW: {
            enemies.insert(new NormalHW(this, Path()));
            break;
        }
        case EnemyType::Essay: {
            enemies.insert(new Essay(this, Path()));
            break;
        }
        case EnemyType::EncryptedHW: {
            enemies.insert(new EncryptedHW(this, Path()));
            break;
        }
        case EnemyType::GroupProj: {
            enemies.insert(new GroupProj(this, Path()));
            break;
        }
        case EnemyType::MathHW: {
            enemies.insert(new MathHW(this, Path()));
            break;
        }
        case EnemyType::COMPLab: {
            enemies.insert(new COMPLab(this, Path()));
            break;
        }
        case EnemyType::PA: {
            enemies.insert(new PA(this, Path()));
            break;
        }
        case EnemyType::Desmond: {
            enemies.insert(new Desmond(this, Path()));
            break;
        }
        case EnemyType::PopQuiz: {
            enemies.insert(new PopQuiz(this, Path()));
            break;
        }
        case EnemyType::Midterm: {
            enemies.insert(new Midterm(this, Path()));
            break;
        }
        case EnemyType::MATHExam: {
            enemies.insert(new MATHExam(this, Path()));
            break;
        }
        case EnemyType::Final: {
            enemies.insert(new Final(this, Path()));
            break;
        }
        case EnemyType::ELPA: {
            enemies.insert(new ELPA(this, Path()));
            break;
        }
        case EnemyType::FYP: {
            enemies.insert(new FYP(this, Path()));
            break;
        }
        default: { // Prevent invalid Inputs
            enemies.insert(new NormalHW(this, Path()));
            break;
        }
    }
}

void EnemyUtility::killEnemy(IEnemy *enemy, bool isDieOfAttack) {
	// get resource if die of attack
	if (isDieOfAttack) {
		// retrieve resource
		gameGrid->resourceManager.gainResource(enemy->getWorth());
	}

	// find &enemy in ememies and remove
	enemies.erase(enemy);

	delete enemy;

	// check if any remaining enemy
	if (/*no more enemy remain*/true || /*no more enemy to spawn*/ true) {
		// proceed to next week
		gameGrid->weekManager.prepareForNextWeek();
    }
}


