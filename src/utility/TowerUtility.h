#ifndef TOWERUTILITY_H
#define TOWERUTILITY_H

#include <set>
using namespace std;

#include "src/map/cell.h"

// forward declaration
class ITower;

class TowerUtility
{
public:
	set<ITower*> refOfTowers; // ref of all towers
	set<Cell*> positionOfTowers;

	~TowerUtility() {
		for (ITower* tower: refOfTowers) {
			delete tower;
		}
}

	void placeTower(TowerType towerType, Cell *position) {
		switch(towerType) {
			case TowerType.Foo:
				 position->content = new Foo(position);
				 break;
			case TowerType.Bar:
				 position->content = new Bar(position);
				 break;
			...
		}
		// update ref list
		refOfTowers.insert(position->content);
		// update position list
		positionOfTowers.insert(position);
	}

	void removeTower(Cell *position) {
		// find &tower in refOfTowers and remove
		refOfTowers.erase(position->content);
		// find position in positionOfTowers and remove
		positionOfTowers.erase(position);
		// delete pointer
		delete position->content;
		position->content = nullptr;
	}
};

#endif // TOWERUTILITY_H
