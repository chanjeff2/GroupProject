#include "cell.h"
#include "GameGrid.h"
#include "src/tower/ITower.h"

Cell::Cell(int x, int y): x(x), y(y), tower(nullptr) {};

Cell::Cell(int x, int y, ITower *tower): x(x), y(y), tower(tower) {};
