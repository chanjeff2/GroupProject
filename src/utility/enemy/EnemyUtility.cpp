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
	QString imgPath_rage = "";
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
			imgPath_rage = ":/res/res/enemies_images/DesmondEnraged Grid";
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
			imgPath_rage = ":/res/res/enemies_images/FinalExam Enraged Grid";
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

	string enemyNameTag = ENEMY_NAME[static_cast<int>(enemyType) - static_cast<int>(EnemyType::NormalHW)];
	newEnemy->id = enemyNameTag + '_' + to_string(enemyID_index);
	++enemyID_index;

	qDebug() << "EnemyUtility: generate enemy" << *newEnemy;

	enemies.insert(newEnemy);
    // group for enemy img and hp bar
	GraphicsItemGroup *group = new GraphicsItemGroup();
	QGraphicsSimpleTextItem *enemyTag = new QGraphicsSimpleTextItem(QString::fromStdString(enemyNameTag));
	enemyTag->setFont(QFont("Arial", 8));
	enemyTag->setZValue(static_cast<float>(Element::ID_Tag));
	enemyTag->setY(- HP_BAR_BG_SIZE.second * 2); // move up
	enemyTag->setX(CELL_SIZE.first / 2 - enemyTag->boundingRect().width() / 2); // move to center
	group->addToGroup(enemyTag);
    // enemy img
	QGraphicsPixmapItem *img = new QGraphicsPixmapItem(QPixmap(imgPath));
	img->setVisible(true);
	img->setZValue(static_cast<float>(Element::Enemy));
	group->addToGroup(img);
    // bg for hp bar
	QRectF hp_bg_rect(0, 0, HP_BAR_BG_SIZE.first, HP_BAR_BG_SIZE.second);
	hp_bg_rect.moveCenter(QPointF(CELL_SIZE.first / 2, 0));
	QGraphicsRectItem *hp_bg = new QGraphicsRectItem(hp_bg_rect);
    hp_bg->setBrush(QColor(HP_BAR_BG_GREY.c_str()));
	hp_bg->setPen(Qt::NoPen);
	hp_bg->setZValue(static_cast<int>(Element::HP_bg));
	group->addToGroup(hp_bg);
    // hp bar
	QRectF hp_rect(0, 0, HP_BAR_SIZE.first, HP_BAR_SIZE.second);
	hp_rect.moveCenter(QPointF(CELL_SIZE.first / 2, 0));
	QGraphicsRectItem *hp = new QGraphicsRectItem(hp_rect);
    hp->setBrush(QColor(HP_BAR_GREEN.c_str()));
	hp->setPen(Qt::NoPen);
	hp->setZValue(static_cast<int>(Element::HP));
	group->addToGroup(hp);

	gameGrid->getScene()->addItem(group);

	newEnemy->attachImageViews(group, hp, img);
	newEnemy->setImgPath(imgPath, imgPath_rage);
	newEnemy->trigger();
}

void EnemyUtility::killEnemy(IEnemy *enemy, KillStatus killStatus) {
	// get resource if die of attack
	switch (killStatus) {
		case KillStatus::DieOfAttack:
			qDebug().nospace() << "EnemyUtility: kill enemy " << *enemy << " by attack"
					 << " at " << *enemy->getPath().getCurrentCell();
			// retrieve resource
			gameGrid->resourceManager.gainResource(enemy->getWorth());
			break;
		case KillStatus::DieOfDeadline:
			qDebug() << "EnemyUtility: kill enemy" << *enemy << "by deadline";
			// reduce gpa
			switch (gameGrid->gpaManager.reduceGPA(enemy->getWorth() * DAMAGE_RATIO)) {
				case GPAManager::GameStatus::GameContinue:
					break;
				case GPAManager::GameStatus::GameOver:
				case GPAManager::GameStatus::GameNotStarted:
					// hand over to game reset for remaining actions
					return;
			}
			break;
		case KillStatus::Reset:
			qDebug() << "EnemyUtility: kill enemy" << *enemy << "by reset";
			// do nothing
			break;
	}

	// find &enemy in ememies and remove
	enemies.erase(enemy);

	// remove enemy from cell
	enemy->getPath().getCurrentCell()->removeEnemy(enemy);

	enemy->die();

	// check if any remaining enemy
	if (enemies.empty()) {
		// proceed to next week
		gameGrid->weekManager.prepareForNextWeek(); // will check if all enemy generated
    }
}

void EnemyUtility::killAllEnemies() {
	qDebug() << "EnemyUtility: kill all enemy";
    gameGrid->weekManager.stopGeneration();

	auto tempEmptyList = enemies;
	for (IEnemy* guy : tempEmptyList) {
		killEnemy(guy, KillStatus::Reset);
	}
}


