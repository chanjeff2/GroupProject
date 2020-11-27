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
			newEnemy = new Essay(this, path);
            break;
        }
        case EnemyType::EncryptedHW: {
			newEnemy = new EncryptedHW(this, path);
            break;
        }
        case EnemyType::GroupProj: {
			newEnemy = new GroupProj(this, path);
            break;
        }
        case EnemyType::MathHW: {
			newEnemy = new MathHW(this, path);
            break;
        }
        case EnemyType::COMPLab: {
			newEnemy = new COMPLab(this, path);
            break;
        }
        case EnemyType::PA: {
			newEnemy = new PA(this, path);
            break;
        }
        case EnemyType::Desmond: {
			newEnemy = new Desmond(this, path);
            break;
        }
        case EnemyType::PopQuiz: {
			newEnemy = new PopQuiz(this, path);
            break;
        }
        case EnemyType::Midterm: {
			newEnemy = new Midterm(this, path);
            break;
        }
        case EnemyType::MATHExam: {
			newEnemy = new MATHExam(this, path);
            break;
        }
        case EnemyType::Final: {
			newEnemy = new Final(this, path);
            break;
        }
        case EnemyType::ELPA: {
			newEnemy = new ELPA(this, path);
            break;
        }
        case EnemyType::FYP: {
			newEnemy = new FYP(this, path);
            break;
        }
        default: { // Prevent invalid Inputs
			newEnemy = new NormalHW(this, path);
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


