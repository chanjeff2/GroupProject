#include "EnemyUtility.h"
#include "src/utility/GameValues.h"
#include "src/enemy/IEnemy.h"
#include "src/map/GameGrid.h"

#include "src/enemy/implementation/NormalHW.h"

EnemyUtility::EnemyUtility(GameGrid *gameGrid): gameGrid(gameGrid) {};

EnemyUtility::~EnemyUtility() {
    for (IEnemy *enemy: enemies) {
        delete enemy;
    }
}

void EnemyUtility::generateEnemy(EnemyType enemyType) {
	IEnemy *newEnemy;
	QString imgPath;
	Path path = gameGrid->getPathStartEnd();
    // Each homework type are separate classes (to be added)
    switch(enemyType) {
        case EnemyType::NormalHW: {
			newEnemy = new NormalHW(this, path);
			imgPath = ":/res/res/enemies_images/NormalHW Grid"; // img path - tbc
            break;
        }
        case EnemyType::Essay: {
			newEnemy = new Essay(START);
            break;
        }
        case EnemyType::EncryptedHW: {
			newEnemy = new EncryptedHW(START);
            break;
        }
        case EnemyType::GroupProj: {
			newEnemy = new GroupProj(START);
            break;
        }
        case EnemyType::MathHW: {
			newEnemy = new MathHW(START);
            break;
        }
        case EnemyType::COMPLab: {
			newEnemy = new COMPLab(START);
            break;
        }
        case EnemyType::PA: {
			newEnemy = new PA(START);
            break;
        }
        case EnemyType::Desmond: {
			newEnemy = new Desmond(START);
            break;
        }
        case EnemyType::PopQuiz: {
			newEnemy = new PopQuiz(START);
            break;
        }
        case EnemyType::Midterm: {
			newEnemy = new Midterm(START);
            break;
        }
        case EnemyType::MATHExam: {
			newEnemy = new MATHExam(START);
            break;
        }
        case EnemyType::Final: {
			newEnemy = new Final(START);
            break;
        }
        case EnemyType::ELPA: {
			newEnemy = new ELPA(START);
            break;
        }
        case EnemyType::FYP: {
			newEnemy = new FYP(START);
            break;
        }
        default: { // Prevent invalid Inputs
			newEnemy = new NormalHW(START);
            break;
        }
    }

	enemies.insert(newEnemy);
	QGraphicsPixmapItem *img = this->gameGrid->getScene()->addPixmap(QPixmap(imgPath));
	newEnemy->attachImageView(img);
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


