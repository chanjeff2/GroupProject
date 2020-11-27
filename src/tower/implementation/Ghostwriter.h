#ifndef GHOSTWRITER_H
#define GHOSTWRITER_H

#include "src/tower/ITower.h"

class Ghostwriter : public ITower
{
public:
    Ghostwriter(Cell* position, TowerUtility *towerUtility);
};

#endif // GHOSTWRITER_H
