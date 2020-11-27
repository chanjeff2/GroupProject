#ifndef REGULAR_H
#define REGULAR_H

#include "ITower.h"

class Regular : public ITower
{
public:
	Regular(Cell* position, TowerUtility *towerUtility);
};

#endif // REGULAR_H
