#ifndef CELL_H
#define CELL_H

// forward declaration
class ITower;
class GameGrid;

class Cell
{
	friend class GameGrid; // cell can only be created when map init

    public:
        const int x;
        const int y;
        ITower *tower;
        Cell(int x, int y);
        Cell(int x, int y, ITower *tower);
};

#endif // CELL_H
