#ifndef PATHFINDINGUTILITY_H
#define PATHFINDINGUTILITY_H

#include <deque>
#include <set>
using namespace std;

#include "Path.h"
#include "src/utility/GameValues.h"

const Coordinate nullCoordinate = make_pair(-1, -1);

// forward declaration
class Cell;
class ITower;
class IEnemy;
class GameGrid;

class PathFindingUtility
{
private:
	class PathBuffer {
	public:
		Path path; // calculated path for
		IEnemy *enemy{nullptr}; // corresponding enemy
		PathBuffer(Path path, IEnemy *enemy);
	};
	
	class CellDetails {
	public:
		Coordinate prevCell{nullCoordinate}; // previous cell **start from end**
		int f{NUM_OF_COL * NUM_OF_ROW}; // f = g + h
		int g{NUM_OF_COL * NUM_OF_ROW}; // cost from start to this cell
		int h{NUM_OF_COL * NUM_OF_ROW}; // cost from this cell to end
	};

	const Coordinate entry;
	const Coordinate exit;
	Path pathStartEnd; // path from entry to exit
	Path pathStartEndBuffer; // buffer to store preview
	set<PathBuffer*> pathBuffer; // buffer for each enemy
	const GameGrid *gameGrid; // ref to game grid

	Path processPath(CellDetails cellDetails[NUM_OF_COL][NUM_OF_ROW], const Coordinate end);

	bool isCoordinateBlocked(Coordinate coordinate, const set<Coordinate> &blockedPosition) const;
	bool isCoordinateBlocked(int x, int y, const set<Coordinate> &blockedPosition) const;

	bool isValidCoordinate(Coordinate coordinate) const;
	bool isValidCoordinate(int x, int y) const;

	/**
	 * @brief findPath - by A* algorithm
	 * @param start
	 * @param end
	 * @param blockedPosition
	 * @return Path {deque<Cell*> from_start_to_end, int total_distance>} ; or empty Path if not found
	 */
	Path findPath(const Coordinate start, const Coordinate end, const set<Coordinate> &blockedPosition = set<Coordinate>());

	bool isEnemyOnPath(const IEnemy *enemy, const Path &path);

public:
	PathFindingUtility(GameGrid *gameGrid);

	Path getPathStartEnd() const;

	/* return buffer storing validated path for each enemy
	 * empty vector if not valid */
	bool validateTowerPlacement(const set<Coordinate> &positionOfTowers, const set<IEnemy*> &enemies);

	/* successfully updated path -> true
	 * failed, path is blocked -> false */
	bool updatePath();
};

#endif // PATHFINDINGUTILITY_H
