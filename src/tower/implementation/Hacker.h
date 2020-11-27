#ifndef HACKER_H
#define HACKER_H

#include "src/tower/ITower.h"

class Hacker : public ITower
{
public:
    Hacker(Cell* position, TowerUtility *towerUtility);
};

#endif // HACKER_H
