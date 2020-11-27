#ifndef ARTS_H
#define ARTS_H

#include "src/tower/ITower.h"

class Arts : public ITower
{
public:
    Arts(Cell* position, TowerUtility *towerUtility);
};

#endif // ARTS_H
