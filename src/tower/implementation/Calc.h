#ifndef CALC_H
#define CALC_H

#include "src/tower/ITower.h"

class Calc : public ITower
{
public:
    Calc(Cell* position, TowerUtility *towerUtility);
};

#endif // CALC_H
