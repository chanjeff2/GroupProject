#ifndef WEEKMANAGER_H
#define WEEKMANAGER_H

#include <vector>
using namespace std;

#include <QObject>
#include <QTimer>
#include "WeekLayoutManager.h"

// forward declaration
enum class EnemyType;
class GameGrid;

class WeekManager: public QObject {
	int week; // wave
	bool isWeekCooldown; // true -> ready to start next week
	atomic_int skippedWeeks; // no. of weeks skipped ** atomic for thread safe
	QTimer* timer;
	WeekLayoutManager* weekLayoutManager;

	GameGrid *gameGrid;

	// wave of enemy to be generate
	int numOfWeeks{0};
	vector<vector<EnemyType>> weeksOfEnemies;

	void loadEnemy(const string& fileName);

	void goToNextWeek();

	// iterate and generate enemies in week
	void processWeek();
	void generateEnemy(EnemyType enemyType);

	// end the game
	void wrapUp();
public:
	// constructor
	WeekManager(GameGrid *gameGrid);

	// getter
	int getWeek() const;

	bool isSkippedWeek() const;

	// methods

	// user manually skip to next week
	void skipToNextWeek();

	// system automatically proceed to next week after last enemy die
	void prepareForNextWeek();

    WeekLayoutManager* accessToLayoutManager() const;
};

#endif // WEEKMANAGER_H
