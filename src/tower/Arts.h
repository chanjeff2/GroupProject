#ifndef ARTS_H
#define ARTS_H

#include "ITower.h"

class Arts : public ITower
{
public:
    Arts(Cell* position, TowerUtility *towerUtility);
};

#endif // ARTS_H
