#include "TowerUtility.h"
#include "src/tower/ITower.h"
#include "src/map/cell.h"
#include "src/tower/aura/AuraEffect.h"
#include "src/map/GameGrid.h"

#include <cmath>
#include <QDebug>

#include "src/tower/implementation/Regular.h"
#include "src/tower/implementation/Arts.h"
#include "src/tower/implementation/WolframAlpha.h"
#include "src/tower/implementation/Hacker.h"
#include "src/tower/implementation/Calc.h"
#include "src/tower/implementation/Nerd.h"
#include "src/tower/implementation/Ghostwriter.h"
#include "src/tower/implementation/Chegg.h"

// init of static member
set<ITower*> TowerUtility::refOfTowers;
set<ITower*> TowerUtility::refOfAuraTowers;

TowerUtility::TowerUtility(GameGrid *gameGrid): gameGrid(gameGrid) {};
TowerUtility::~TowerUtility() {
    for (ITower* tower: refOfTowers) {
        delete tower;
    }
}

QGraphicsRectItem* TowerUtility::drawRange(std::pair<int,int> position, TowerType tower_type, QGraphicsScene& scene) {
    int tower_range = TOWER_RANGES[int(tower_type)];
    AuraType aura_type = TOWER_AURAS[int(tower_type)];

    int starting_pos_x = fmax( 0 , CELL_SIZE.first * ( position.first - tower_range ) );
    int starting_pos_y = fmax( 0 , CELL_SIZE.second * ( position.second - tower_range ) );
    int ending_pos_x = fmin(CELL_SIZE.first * NUM_OF_COL , CELL_SIZE.first * ( position.first + tower_range + 1 ) );
    int ending_pos_y = fmin( CELL_SIZE.second * NUM_OF_ROW , CELL_SIZE.second * ( position.second + tower_range + 1) );
    int length_x = ending_pos_x - starting_pos_x;
    int length_y = ending_pos_y - starting_pos_y;

    QBrush range_color;
    switch (aura_type) {
        case AuraType::Null: case AuraType::RageAura:
            range_color = Qt::NoBrush; break;
        case AuraType::SlowAura:
            range_color = QColor(28, 118, 199, 100); break;
        case AuraType::ArmorPierceAura:
            range_color = QColor(85, 85, 85, 100); break;
    }

    QGraphicsRectItem * rangeRect = scene.addRect(QRect( starting_pos_x , starting_pos_y , length_x , length_y ) , QPen(Qt::black) , range_color);
    return rangeRect;
}

void TowerUtility::placeTower(TowerType towerType, Cell *position) {
    // Each tower type are separate classes (to be added)
	ITower *newTower;
	QString imgPath;

    switch(towerType) {
        case TowerType::Regular: {
			 newTower = new Regular(position, this);
			 imgPath = ":/res/res/towers_images/RegularStudent Grid";
             break;
        }
        case TowerType::Arts: {
			 newTower = new Arts(position, this);
			 imgPath = ":/res/res/towers_images/ArtsStudent Grid";
             break;
        }
        case TowerType::WolframAlpha: {
			newTower = new WolframAlpha(position, this);
			imgPath = ":/res/res/towers_images/Wolfram Grid";
            break;
        }
        case TowerType::Hacker: {
			newTower = new Hacker(position, this);
			imgPath = ":/res/res/towers_images/Hackerman Grid";
            break;
        }
        case TowerType::Calc: {
			newTower = new Calc(position, this);
			imgPath = ":/res/res/towers_images/Calculator Grid";
            break;
        }
        case TowerType::Nerd: {
			newTower = new Nerd(position, this);
			imgPath = ":/res/res/towers_images/Nerd Grid";
            break;
        }
        case TowerType::Ghostwriter: {
			newTower = new Ghostwriter(position, this);
			imgPath = ":/res/res/towers_images/Ghostwriter Grid";
            break;
        }
        case TowerType::Chegg: {
			newTower = new Chegg(position, this);
			imgPath = ":/res/res/towers_images/Chegg Grid";
            break;
        }
        case TowerType::None: { // No towers selected
			return;
        }
        default: { // Prevent invalid Inputs
			newTower = new Regular(position, this);
			imgPath = ":/res/res/towers_images/RegularStudent Grid";
            break;
        }
    }

	newTower->id = TOWER_NAME[static_cast<int>(towerType)] + '_' + to_string(towerID_index);
	++towerID_index;

	qDebug().nospace() << "TowerUtility: place tower " << *newTower
					   << " at " << *position;

    // update ref list
	refOfTowers.insert(newTower);
    if (newTower->auraEffect->getAuraType() != AuraType::Null) {
		refOfAuraTowers.insert(newTower);
	}
	position->placeTower(newTower);
    // update position list
	positionOfTowers.insert(make_pair(position->x, position->y));

	QGraphicsPixmapItem *img = this->gameGrid->getScene()->addPixmap(QPixmap(imgPath));

    /*

    int starting_pos_x = fmax( 0 , CELL_SIZE.first * ( position->x - newTower->getRange() ) );
    int starting_pos_y = fmax( 0 , CELL_SIZE.second * ( position->y - newTower->getRange() ) );
    int ending_pos_x = fmin(CELL_SIZE.first * NUM_OF_COL , CELL_SIZE.first * ( position->x + newTower->getRange() + 1 ) );
    int ending_pos_y = fmin( CELL_SIZE.second * NUM_OF_ROW , CELL_SIZE.second * ( position->y + newTower->getRange() + 1) );
    int length_x = ending_pos_x - starting_pos_x;
    int length_y = ending_pos_y - starting_pos_y;

    QBrush range_color;
    switch (newTower->auraEffect->getAuraType()) {
        case AuraType::Null: case AuraType::RageAura:
            range_color = Qt::NoBrush; break;
        case AuraType::SlowAura:
            range_color = QColor(28, 118, 199, 100); break;
        case AuraType::ArmorPierceAura:
            range_color = QColor(85, 85, 85, 100); break;
    }

    QGraphicsRectItem * rangeRect = this->gameGrid->getScene()->addRect(QRect( starting_pos_x , starting_pos_y , length_x , length_y ) , QPen(Qt::black) , range_color);
    */


    QGraphicsRectItem* rangeRect = TowerUtility::drawRange( make_pair(position->x,position->y) , newTower->getTowerType() , *(this->gameGrid->getScene()) );

    if ( newTower->auraEffect->getAuraType() == AuraType::Null ) {
        rangeRect->setVisible(false);
    }
    newTower->attachImageView(img, rangeRect);
}

void TowerUtility::removeTower(Cell *position) {
	qDebug().nospace() << "TowerUtility: remove tower " << *position->getTower()
					   << " at " << *position;

	// redemption
	int redemption = round(position->getTower()->getCost() * REDEMPTION_RATIO);
	gameGrid->resourceManager.gainResource(redemption);

	// find &tower in refOfTowers and remove
	refOfTowers.erase(position->getTower());
    if (position->getTower()->auraEffect->getAuraType() != AuraType::Null) {
		refOfAuraTowers.erase(position->getTower());
	}
	// find position in positionOfTowers and remove
	positionOfTowers.erase(make_pair(position->x, position->y));
	// remove tower in cell
	position->removeTower();
}

Cell *TowerUtility::getCell(int x, int y) const {
	return gameGrid->getCell(x, y);
}

int TowerUtility::getCost(TowerType towerType) const {
	if (towerType == TowerType::None) {
		return 0;
	}
	return TOWER_PRICES[static_cast<int>(towerType)];
}

bool TowerUtility::isValidCoordinate(int x, int y) const {
	return gameGrid->isValidCoordinate(x, y);
}

