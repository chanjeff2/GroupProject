#include "WeekManager.h"
#include "src/utility/GameValues.h"
#include "WeekLayoutManager.h"

#include <fstream>
#include <sstream>
#include <string>
#include <QFileDialog>
#include <QDebug>

// constructor
WeekManager::WeekManager() {
	week = 0;
	isWeekCooldown = true;
	skippedWeeks = 0;

	timer = new QTimer(this);
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

	// cooldown week skip
	QTimer::singleShot(WEEK_COOLDOWN * 1000, this, SLOT([]{
		isWeekCooldown = true
		weekLayoutManager.isWeekCoolDown(true);
	}));
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
	ifstream enemyFile(fileName);

	if (!enemyFile) {
		qDebug() << "Error: cannot open " << QString::fromStdString(fileName);
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
		weeksOfEnemies.push_back(listOfEnemy);
	}

	enemyFile.close();
}

// user manually skip to next week
void WeekManager::skipToNextWeek() {
	// increment skip counter
	++skippedWeeks;

	goToNextWeek();
}

// system automatically proceed to next week after last enemy die
void WeekManager::prepareForNextWeek() {
	if (!isSkippedWeek()) {
        weekLayoutManager->weekCountDown(WEEK_COUNTDOWN);
	}
	// start count down timer to proceed to next week
	// cooldown week skip
	QTimer::singleShot(WEEK_COUNTDOWN * 1000, this, SLOT([]{
		if (!isSkippedWeek())
			goToNextWeek();
		else
			skippedWeeks--;
	}));
}

WeekLayoutManager* WeekManager::accessToLayoutManager() const {
    return weekLayoutManager;
}
