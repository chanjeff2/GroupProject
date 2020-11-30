#include "EnemyUtility.h"
#include "src/utility/GameValues.h"
#include "src/enemy/IEnemy.h"
#include "src/utility/pathfinding/Path.h"
#include "src/map/GameGrid.h"
#include "src/map/cell.h"

#include <QDebug>

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
			imgPath = ":/res/res/enemies_images/Essay Grid";
			break;
		}
		case EnemyType::EncryptedHW: {
			newEnemy = new EncryptedHW(this, path);
			imgPath = ":/res/res/enemies_images/Encrypted Grid";
			break;
		}
		case EnemyType::GroupProj: {
			newEnemy = new GroupProj(this, path);
			imgPath = ":/res/res/enemies_images/GpPrj Grid";
			break;
		}
		case EnemyType::MathHW: {
			newEnemy = new MathHW(this, path);
			imgPath = ":/res/res/enemies_images/MathHW1 Grid";
			break;
		}
		case EnemyType::COMPLab: {
			newEnemy = new COMPLab(this, path);
			imgPath = ":/res/res/enemies_images/COMPLab Grid";
			break;
		}
		case EnemyType::PA: {
			newEnemy = new PA(this, path);
			imgPath = ":/res/res/enemies_images/PA Grid";
			break;
		}
		case EnemyType::Desmond: {
			newEnemy = new Desmond(this, path);
			imgPath = ":/res/res/enemies_images/Desmond Grid";
			break;
		}
		case EnemyType::PopQuiz: {
			newEnemy = new PopQuiz(this, path);
			imgPath = ":/res/res/enemies_images/PopQuiz1 Grid";
			break;
		}
		case EnemyType::Midterm: {
			newEnemy = new Midterm(this, path);
			imgPath = ":/res/res/enemies_images/Midterm Grid";
			break;
		}
		case EnemyType::MATHExam: {
			newEnemy = new MATHExam(this, path);
			imgPath = ":/res/res/enemies_images/MathsExam Grid";
			break;
		}
		case EnemyType::Final: {
			newEnemy = new Final(this, path);
			imgPath = ":/res/res/enemies_images/FinalExam Grid";
			break;
		}
		case EnemyType::ELPA: {
			newEnemy = new ELPA(this, path);
			imgPath = ":/res/res/enemies_images/ELPA Grid";
			break;
		}
		case EnemyType::FYP: {
			newEnemy = new FYP(this, path);
			imgPath = ":/res/res/enemies_images/FYP Grid";
			break;
		}
		default: { // Prevent invalid Inputs
			newEnemy = new NormalHW(this, path);
			imgPath = ":/res/res/enemies_images/NormalHW Grid";
			break;
		}
	}

	newEnemy->id = ENEMY_NAME[static_cast<int>(enemyType)] + '_' + static_cast<char>(enemyID_index);
	++enemyID_index;

	qDebug() << "EnemyUtility: generate enemy" << QString::fromStdString(newEnemy->id);

	enemies.insert(newEnemy);
	QGraphicsPixmapItem *img = this->gameGrid->getScene()->addPixmap(QPixmap(imgPath));
	newEnemy->attachImageView(img);
}

void EnemyUtility::killEnemy(IEnemy *enemy, bool isDieOfAttack) {
	// get resource if die of attack
	if (isDieOfAttack) {
		qDebug().nospace() << "EnemyUtility: kill enemy " << QString::fromStdString(enemy->id) << " by attack"
				 << " at (" << enemy->getPath().getCurrentCoordinate() << ")";
		// retrieve resource
		gameGrid->resourceManager.gainResource(enemy->getWorth());
	} else {
		qDebug() << "EnemyUtility: kill enemy" << QString::fromStdString(enemy->id) << "by deadline";
		// reduce gpa
		gameGrid->gpaManager.reduceGPA(enemy->getWorth() * DAMAGE_RATIO);
	}

	// remove enemy from cell
	enemy->getPath().getCurrentCell()->removeEnemy(enemy);

	// find &enemy in ememies and remove
	enemies.erase(enemy);

	delete enemy;

	// check if any remaining enemy
	if (enemies.empty()) {
		// proceed to next week
		gameGrid->weekManager.prepareForNextWeek(); // will check if all enemy generated
    }
}


