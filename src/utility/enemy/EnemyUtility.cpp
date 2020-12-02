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

#include <stdlib.h>
#include <time.h>

EnemyUtility::EnemyUtility(GameGrid *gameGrid): gameGrid(gameGrid) {
    srand(time(0));
};

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
            // Polymorph enemy - has 3 Forms!
            int rng = (rand() % 3) + 1;
            switch (rng) {
                case 1:
                    imgPath = ":/res/res/enemies_images/MathHW1 Grid"; break;
                case 2:
                    imgPath = ":/res/res/enemies_images/MathHW2 Grid"; break;
                case 3:
                    imgPath = ":/res/res/enemies_images/MathHW3 Grid"; break;
            }
			break;
		}
		case EnemyType::COMPLab: {
			newEnemy = new COMPLab(this, path);
            // Polymorph enemy - has 2 Forms!
            int rng = (rand() % 2) + 1;
            switch (rng) {
                case 1:
                    imgPath = ":/res/res/enemies_images/COMPLab Grid"; break;
                case 2:
                    imgPath = ":/res/res/enemies_images/COMPLab2 Grid"; break;
            }
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
            // Polymorph enemy - has 2 Forms!
            int rng = (rand() % 2) + 1;
            switch (rng) {
                case 1:
                    imgPath = ":/res/res/enemies_images/PopQuiz1 Grid"; break;
                case 2:
                    imgPath = ":/res/res/enemies_images/PopQuiz2 Grid"; break;
            }
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

	newEnemy->id = ENEMY_NAME[static_cast<int>(enemyType) - static_cast<int>(EnemyType::NormalHW)] + '_' + to_string(enemyID_index);
	++enemyID_index;

	qDebug() << "EnemyUtility: generate enemy" << *newEnemy;

	enemies.insert(newEnemy);
	QGraphicsPixmapItem *img = this->gameGrid->getScene()->addPixmap(QPixmap(imgPath));
	PixMap *pixMapimg = new PixMap(img);
    pixMapimg->setOffset( path.getNextCoordinate().first * CELL_SIZE.first , path.getNextCoordinate().second * CELL_SIZE.second );
	newEnemy->attachImageView(pixMapimg);
	newEnemy->trigger();
}

void EnemyUtility::killEnemy(IEnemy *enemy, bool isDieOfAttack) {
	// get resource if die of attack
	if (isDieOfAttack) {
		qDebug().nospace() << "EnemyUtility: kill enemy " << *enemy << " by attack"
				 << " at " << *enemy->getPath().getCurrentCell();
		// retrieve resource
		gameGrid->resourceManager.gainResource(enemy->getWorth());
	} else {
		qDebug() << "EnemyUtility: kill enemy" << *enemy << "by deadline";
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

void EnemyUtility::killAllEnemies() {
    gameGrid->weekManager.stopGeneration();
    /* Originally planned to kill all enemies
     * However it crashes everytime
     * Changed to another plan:
     * 1. Allow all enemy to move to exit
     * 2. Lock the GPA at the same time
     *
     * The original code is shown below
     */
    /* auto tempEmptyList = enemies;
    for (IEnemy* guy : tempEmptyList) {
        killEnemy(guy, false);
    } */
}


