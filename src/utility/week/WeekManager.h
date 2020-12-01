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
    Q_OBJECT
private:
	int week; // wave
	bool isWeekCooldown; // true -> ready to start next week
	bool finishGenerateEnemy{true}; // flag checking if generated all enemy in each week
	atomic_int skippedWeeks; // no. of weeks skipped ** atomic for thread safe
	WeekLayoutManager* weekLayoutManager;

	GameGrid *gameGrid;

	// wave of enemy to be generate
	int numOfWeeks{0};
	vector<vector<EnemyType>> weeksOfEnemies;

	void goToNextWeek();

	// iterate and generate enemies in week
	void processWeek();
	void generateEnemy(vector<EnemyType> &enemyList, int index, int size);

	// end the game
	void wrapUp();
public:
	// constructor
	WeekManager(GameGrid *gameGrid);

	// getter
	int getWeek() const;

	bool isSkippedWeek() const;

	// methods
	void loadEnemy(const string& fileName);

	// user manually skip to next week
	void skipToNextWeek();

	// system automatically proceed to next week after last enemy die
	void prepareForNextWeek();

	void setLayoutManager(WeekLayoutManager* weekLayoutManager);
	
signals:
    void game_beaten();
};

#endif // WEEKMANAGER_H
