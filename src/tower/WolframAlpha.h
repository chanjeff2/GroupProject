#ifndef WOLFRAMALPHA_H
#define WOLFRAMALPHA_H

#include "ITower.h"

class WolframAlpha : public ITower
{
public:
    WolframAlpha(Cell* position, TowerUtility *towerUtility);
};

#endif // WOLFRAMALPHA_H
