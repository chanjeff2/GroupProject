#include "EnemyUtility.h"
#include "src/utility/GameValues.h"
#include "src/enemy/IEnemy.h"
#include "src/map/GameGrid.h"

#include "src/enemy/NormalHW.h"
#include "src/enemy/Essay.h"
#include "src/enemy/EncryptedHW.h"
#include "src/enemy/GroupProj.h"
#include "src/enemy/MathHW.h"
#include "src/enemy/CompLab.h"
#include "src/enemy/PA.h"
#include "src/enemy/Desmond.h"
#include "src/enemy/PopQuiz.h"
#include "src/enemy/Midterm.h"
#include "src/enemy/Final.h"
#include "src/enemy/MathExam.h"
#include "src/enemy/Elpa.h"
#include "src/enemy/Fyp.h"




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
            enemies.insert(new NormalHW(this, Path() ));
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
        case EnemyType::CompLab: {
            enemies.insert(new CompLab(this, Path()));
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
        case EnemyType::MathExam: {
            enemies.insert(new MathExam(this, Path()));
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


