#include "TowerUtility.h"
#include "src/tower/ITower.h"
#include "GameValues.h"
#include "src/map/cell.h"

TowerUtility::TowerUtility() = default;
TowerUtility::~TowerUtility() {
    for (ITower* tower: refOfTowers) {
        delete tower;
    }
}

void TowerUtility::placeTower(TowerType towerType, Cell *position) {
    // Each tower type are separate classes (to be added)
    switch(towerType) {
        case TowerType::Regular: {
             position->tower = new Regular(position);
             break;
        }
        case TowerType::Arts: {
             position->tower = new Arts(position);
             break;
        }
        case TowerType::WolframAlpha: {
            position->tower = new WolframAlpha(position);
            break;
        }
        case TowerType::Hacker: {
            position->tower = new Hacker(position);
            break;
        }
        case TowerType::Calc: {
            position->tower = new Calc(position);
            break;
        }
        case TowerType::Nerd: {
            position->tower = new Nerd(position);
            break;
        }
        case TowerType::Ghostwriter: {
            position->tower = new Ghostwriter(position);
            break;
        }
        case TowerType::Chegg: {
            position->tower = new Chegg(position);
            break;
        }
        case TowerType::None: { // No towers selected
            return; break;
        }
        default: { // Prevent invalid Inputs
            position->tower = new Regular(position);
            break;
        }

    }
    // update ref list
    refOfTowers.insert(position->tower);
    // update position list
    positionOfTowers.insert(position);
}

void TowerUtility::removeTower(Cell *position) {
        // find &tower in refOfTowers and remove
        refOfTowers.erase(position->tower);
        // find position in positionOfTowers and remove
        positionOfTowers.erase(position);
        // delete pointer
        delete position->tower;
        position->tower = nullptr;
    }


