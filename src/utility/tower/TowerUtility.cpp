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

	QGraphicsRectItem* rangeRect = drawRange(newTower, position);

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

int TowerUtility::getRange(TowerType towerType) const {
	return TOWER_RANGES[static_cast<int>(towerType)];
}

bool TowerUtility::isValidCoordinate(int x, int y) const {
	return gameGrid->isValidCoordinate(x, y);
}

QGraphicsRectItem* TowerUtility::drawRange(ITower *tower, Cell *position) {
	// existing tower
	int range = tower->getRange();
	AuraType aura_type = tower->auraEffect->getAuraType();
	Coordinate pos = make_pair(position->x, position->y);

	return drawRange(range, aura_type, pos, false);
}

QGraphicsRectItem* TowerUtility::drawRange(TowerType towertype, Coordinate position) {
	// preview tower
	int range = TOWER_RANGES[static_cast<int>(towertype)];
	AuraType aura_type = TOWER_AURAS[static_cast<int>(towertype)];

	return drawRange(range, aura_type, position, true);
}

QGraphicsRectItem* TowerUtility::drawRange(int range, AuraType aura_type, Coordinate position, bool isPreview) {
	int starting_pos_x = fmax( 0 , CELL_SIZE.first * ( position.first - range ) );
	int starting_pos_y = fmax( 0 , CELL_SIZE.second * ( position.second - range ) );
	int ending_pos_x = fmin(CELL_SIZE.first * NUM_OF_COL , CELL_SIZE.first * ( position.first + range + 1 ) );
	int ending_pos_y = fmin( CELL_SIZE.second * NUM_OF_ROW , CELL_SIZE.second * ( position.second + range + 1) );
	int length_x = ending_pos_x - starting_pos_x;
	int length_y = ending_pos_y - starting_pos_y;

	QBrush range_color;
	switch (aura_type) {
		case AuraType::Null:
		case AuraType::RageAura:
			range_color = Qt::NoBrush;
			break;
		case AuraType::SlowAura:
			if (isPreview) {
				range_color = QColor(28, 118, 199, 100);
			} else {
				range_color = QColor(28, 118, 199, 30);
			}
			break;
		case AuraType::ArmorPierceAura:
			if (isPreview) {
				range_color = QColor(85, 85, 85, 100);
			} else {
				range_color = QColor(85, 85, 85, 30);
			}
			break;
	}

	QGraphicsRectItem *rangeRect = gameGrid->getScene()->addRect(QRect( starting_pos_x , starting_pos_y , length_x , length_y ) , QPen(Qt::black) , range_color);
	rangeRect->setZValue(static_cast<int>(Element::Indicator));

	if (isPreview) {
		rangeRect->setVisible(true);
		return rangeRect;
	}

	switch (aura_type) {
		case AuraType::SlowAura:
		case AuraType::ArmorPierceAura:
			rangeRect->setVisible(true);
			break;
		default:
			rangeRect->setVisible(false);
			break;
	}
	return rangeRect;
}

