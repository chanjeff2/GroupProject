#include "WeekManager.h"
#include "src/utility/GameValues.h"
#include "WeekLayoutManager.h"
#include "src/map/GameGrid.h"

#include <fstream>
#include <sstream>
#include <string>
#include <QFileDialog>
#include <QDebug>

// constructor
WeekManager::WeekManager(GameGrid *gameGrid): gameGrid(gameGrid) {
	week = 0;
	isWeekCooldown = true;
	skippedWeeks = 0;
}

void WeekManager::goToNextWeek() {
	// do nothing if week haven't cooldown
	if (!isWeekCooldown) {
		return;
	}

	isWeekCooldown = false;
    weekLayoutManager->isWeekCoolDown(false);
	// goto next week
	++week;
    weekLayoutManager->updateWeek(week);

	// generate enemy
	processWeek();
}

// getter
int WeekManager::getWeek() const {
	return week;
}

bool WeekManager::isSkippedWeek() const {
	return skippedWeeks > 0;
}

// methods

void WeekManager::loadEnemy(const string& fileName) {
	numOfWeeks = 0;
	ifstream enemyFile(fileName);

	if (!enemyFile) {
		qDebug() << "WeekManager: Error: cannot open " << QString::fromStdString(fileName);
		return;
	}

	while (!enemyFile.eof()) {
		string line_input;
		getline(enemyFile, line_input);
		istringstream line_input_stream(line_input);

		int enemyID;
		vector<EnemyType> listOfEnemy;
		while (line_input_stream >> enemyID) {
			listOfEnemy.push_back(static_cast<EnemyType>(enemyID));
		}
		// skip empty line if any
		if (!listOfEnemy.empty()) {
			weeksOfEnemies.push_back(listOfEnemy);
			++numOfWeeks;
		}
	}

    weekLayoutManager->initNumOfWeeks(numOfWeeks);
	enemyFile.close();

	// start the game
	prepareForNextWeek();
}

void WeekManager::wrapUp() {
    emit game_beaten();
}

void WeekManager::processWeek() {
	if (weeksOfEnemies.empty()) {
		qDebug() << "Error: empty week";
		return;
	}
	vector<EnemyType> &enemyOfThisWeek = weeksOfEnemies.at(week - 1);

	finishGenerateEnemy = false;
	generateEnemy(enemyOfThisWeek, 0, enemyOfThisWeek.size());

}

void WeekManager::generateEnemy(vector<EnemyType> &enemyList, int index, int size) {

	gameGrid->generateEnemy(enemyList.at(index));
	// increment iterator
	if (++index == size) {
		finishGenerateEnemy = true;

		// cooldown week skip
		QTimer::singleShot(WEEK_COOLDOWN * 1000 / GAME_SPEED, [&]{
			qDebug() << "WeekManager: cooldown for next week";
			isWeekCooldown = true;
			weekLayoutManager->isWeekCoolDown(true);
		});

		return;
	}

	QTimer::singleShot(ENEMY_GENERATE_INTERVAL * 1000 / GAME_SPEED, [=, &enemyList]() {
		generateEnemy(enemyList, index, size);
	});
}

// user manually skip to next week
void WeekManager::skipToNextWeek() {
	if (week == numOfWeeks) {
		return;
	}
	qDebug() << "WeekManager: skip to next week";

	// increment skip counter
	++skippedWeeks;

	goToNextWeek();
}

// system automatically proceed to next week after last enemy die
void WeekManager::prepareForNextWeek() {
	qDebug() << "WeekManager: prepare For Next Week";
	if (!finishGenerateEnemy) {
		// prevent start new week before generated all enemy
		return;
	}

	if (week == numOfWeeks) {
		wrapUp();
		return;
	}

	if (!isSkippedWeek()) {
        weekLayoutManager->weekCountDown(WEEK_COUNTDOWN);
	}
	// start count down timer to proceed to next week
	// cooldown week skip
	QTimer::singleShot(WEEK_COUNTDOWN * 1000 / GAME_SPEED, [&]{
		if (!isSkippedWeek())
			goToNextWeek();
		else
			skippedWeeks--;
	});
}

void WeekManager::setLayoutManager(WeekLayoutManager* weekLayoutManager) {
	this->weekLayoutManager = weekLayoutManager;
}
