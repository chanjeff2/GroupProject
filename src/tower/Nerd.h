#ifndef NERD_H
#define NERD_H

#include "ITower.h"

class Nerd : public ITower
{
public:
    Nerd(Cell* position, TowerUtility *towerUtility);
};

#endif // NERD_H
