#ifndef CHEGG_H
#define CHEGG_H

#include "ITower.h"

class Chegg : public ITower
{
public:
    Chegg(Cell* position, TowerUtility *towerUtility);
};

#endif // CHEGG_H
