#ifndef CELL_H
#define CELL_H

#include <set>
#include <QDebug>
#include "src/utility/GameValues.h"
#include <QGraphicsRectItem>
using namespace std;

// forward declaration
class ITower;
class IEnemy;
class GameGrid;
enum class CellType;

class Cell
{
	friend class GameGrid; // cell can only be created when map init
	friend QDebug& operator<<(QDebug &qdebug, const Cell &cell);

	ITower *tower{nullptr};
	set<IEnemy*> enemy;
    CellType cell_type;
	QGraphicsRectItem* cell_squares{nullptr}; // cell img

	// constructor
	Cell(int x, int y);
	Cell(int x, int y, ITower *tower);

public:
	~Cell();
	const int x;
	const int y;

	// getter
	ITower *getTower() const;
	set<IEnemy*> getEnemy() const;

	// setter
	void setCellType(CellType cell_type);

	// methods
	// true -> successfully placed
	bool placeTower(ITower *tower);
	void removeTower();

	void addEnemy(IEnemy *enemy);
	void removeEnemy(IEnemy *enemy);

	// no enemy nor tower
	bool isEmpty() const;

	bool hasTower() const;
};

#endif // CELL_H
