#include "EnemyUtility.h"
#include "src/utility/GameValues.h"
#include "src/enemy/IEnemy.h"
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
            enemies.insert(new NormalHW(START));
            break;
        }
        case EnemyType::Essay: {
            enemies.insert(new Essay(START));
            break;
        }
        case EnemyType::EncryptedHW: {
            enemies.insert(new EncryptedHW(START));
            break;
        }
        case EnemyType::GroupProj: {
            enemies.insert(new GroupProj(START));
            break;
        }
        case EnemyType::MathHW: {
            enemies.insert(new MathHW(START));
            break;
        }
        case EnemyType::COMPLab: {
            enemies.insert(new COMPLab(START));
            break;
        }
        case EnemyType::PA: {
            enemies.insert(new PA(START));
            break;
        }
        case EnemyType::Desmond: {
            enemies.insert(new Desmond(START));
            break;
        }
        case EnemyType::PopQuiz: {
            enemies.insert(new PopQuiz(START));
            break;
        }
        case EnemyType::Midterm: {
            enemies.insert(new Midterm(START));
            break;
        }
        case EnemyType::MATHExam: {
            enemies.insert(new MATHExam(START));
            break;
        }
        case EnemyType::Final: {
            enemies.insert(new Final(START));
            break;
        }
        case EnemyType::ELPA: {
            enemies.insert(new ELPA(START));
            break;
        }
        case EnemyType::FYP: {
            enemies.insert(new FYP(START));
            break;
        }
        default: { // Prevent invalid Inputs
            enemies.insert(new NormalHW(START));
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


