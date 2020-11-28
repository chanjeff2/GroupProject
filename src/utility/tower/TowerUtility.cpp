#include "TowerUtility.h"
#include "src/tower/ITower.h"
#include "src/utility/GameValues.h"
#include "src/map/cell.h"
#include "src/tower/aura/AuraEffect.h"
#include "src/map/GameGrid.h"

#include <cmath>

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

    switch(towerType) {
        case TowerType::Regular: {
			 newTower = new Regular(position, this);
             break;
        }
        case TowerType::Arts: {
			 newTower = new Arts(position, this);
             break;
        }
        case TowerType::WolframAlpha: {
			newTower = new WolframAlpha(position, this);
            break;
        }
        case TowerType::Hacker: {
			newTower = new Hacker(position, this);
            break;
        }
        case TowerType::Calc: {
			newTower = new Calc(position, this);
            break;
        }
        case TowerType::Nerd: {
			newTower = new Nerd(position, this);
            break;
        }
        case TowerType::Ghostwriter: {
			newTower = new Ghostwriter(position, this);
            break;
        }
        case TowerType::Chegg: {
			newTower = new Chegg(position, this);
            break;
        }
        case TowerType::None: { // No towers selected
            return; break;
        }
        default: { // Prevent invalid Inputs
			newTower = new Regular(position, this);
            break;
        }
    }
    // update ref list
	refOfTowers.insert(newTower);
    if (newTower->auraEffect->getAuraType() != AuraType::Null) {
		refOfAuraTowers.insert(newTower);
	}
	position->placeTower(newTower);
    // update position list
	positionOfTowers.insert(make_pair(position->x, position->y));
}

void TowerUtility::removeTower(Cell *position) {
	// redemption
	int redemption = round(position->getTower()->getCost() * REDEMPTION_RATIO);
	gameGrid->resourceManager.gainResource(redemption);

	// find &tower in refOfTowers and remove
	refOfTowers.erase(position->getTower());
    if (position->getTower()->auraEffect->getAuraType() != AuraType::Null) {
		refOfAuraTowers.insert(position->getTower());
	}
	// find position in positionOfTowers and remove
	positionOfTowers.erase(make_pair(position->x, position->y));
	// remove tower in cell
	position->removeTower();
}

Cell *TowerUtility::getCell(int x, int y) const {
	return gameGrid->getCell(x, y);
}

