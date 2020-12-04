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

    if (!isGameStarted) return;

	// do nothing if week haven't cooldown
	if (!isWeekCooldown) {
		return;
	}
	qDebug() << "WeekManager: go to Next Week";

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

bool WeekManager::loadEnemy(const string& fileName) {
	numOfWeeks = 0;
	ifstream enemyFile(fileName);

	if (!enemyFile) {
		qDebug() << "WeekManager: Error: cannot open " << QString::fromStdString(fileName);
        return false;
	}

	while (!enemyFile.eof()) {
		string line_input;
		getline(enemyFile, line_input);
		istringstream line_input_stream(line_input);

		int enemyID;
		vector<EnemyType> listOfEnemy;
		while (line_input_stream >> enemyID) {
			if (static_cast<int>(EnemyType::NormalHW) > enemyID || enemyID >= static_cast<int>(EnemyType::_END_POINTER)) {
                // invalid input
                qDebug() << "WeekManager: Error: invalid enemy ID from" << QString::fromStdString(fileName);
                // close file
                enemyFile.close();
                // reset values
                weeksOfEnemies.clear();
                numOfWeeks = 0;
                return false;
            }
			listOfEnemy.push_back(static_cast<EnemyType>(enemyID));
		}
		// skip empty line if any
		if (!listOfEnemy.empty()) {
			weeksOfEnemies.push_back(listOfEnemy);
			++numOfWeeks;
		}
	}

	if (numOfWeeks == 0) {
		qDebug() << "WeekManager: Error: no enemy ID can be loaded from" << QString::fromStdString(fileName);
		// close file
		enemyFile.close();
		// reset values
		weeksOfEnemies.clear();
		numOfWeeks = 0;
		return false;
	}

    weekLayoutManager->initNumOfWeeks(numOfWeeks);
	enemyFile.close();

    return true;
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

    if (isGameOver) return;

	gameGrid->generateEnemy(enemyList.at(index));
	// increment iterator
	if (++index == size) {
		finishGenerateEnemy = true;

		// cooldown week skip
		QTimer::singleShot(WEEK_COOLDOWN * 1000 / GAME_SPEED, [&]{
			qDebug() << "WeekManager: cooldown for next week";
			isWeekCooldown = true;
            if (week < numOfWeeks)
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
	if (gameGrid->getAllEnemy().empty()) {
		// increment skippedWeeks to cancel emitted prepareForNextWeek()
		++skippedWeeks;
	}
	weekLayoutManager->isSkipped = true;

	goToNextWeek();
}

// system automatically proceed to next week after last enemy die
void WeekManager::prepareForNextWeek() {

    if (!isGameStarted) return;

	qDebug() << "WeekManager: prepare For Next Week";
    if (!finishGenerateEnemy) {
		// prevent start new week before generated all enemy
		return;
	}

    if (week == numOfWeeks) {
        isGameStarted = false;
		wrapUp();
		return;
	}

	weekLayoutManager->isSkipped = false;
	weekLayoutManager->weekCountDown(WEEK_COUNTDOWN);

	// start count down timer to proceed to next week
	// cooldown week skip
	weekCountDown(WEEK_COUNTDOWN);
}

void WeekManager::weekCountDown(int time) {
	if (time == 0) {
		if (!isSkippedWeek()) {
			goToNextWeek();
		} else {
			qDebug() << "WeekManager: skippedWeeks--";
			skippedWeeks--;
		}
	} else {
		QTimer::singleShot(1000 / GAME_SPEED, [&, time] { weekCountDown(time - 1); });
	}
}

void WeekManager::setLayoutManager(WeekLayoutManager* weekLayoutManager) {
	this->weekLayoutManager = weekLayoutManager;
}

void WeekManager::stopGeneration() {
    isGameOver = true;
}

void WeekManager::toggle_game_started(bool game_started) {
    isGameStarted = game_started;
}

void WeekManager::manager_reset() {
    week = 0;
    isWeekCooldown = true;
    isGameOver = false;
    isGameStarted = false;
    skippedWeeks = 0;
    finishGenerateEnemy = true;
    weeksOfEnemies.clear();
    weekLayoutManager->isWeekCoolDown(false);
    weekLayoutManager->updateWeek(week);
    weekLayoutManager->initNumOfWeeks(14); // 14 is the default value, shouldn't affect appearance
}
