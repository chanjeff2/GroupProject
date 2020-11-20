#ifndef WEEKMANAGER_H
#define WEEKMANAGER_H

#include <QObject>
#include <QTimer>
#include "GameValues.h"

class WeekManager: public QObject {
	int week; // wave
	bool isWeekCooldown; // true -> ready to start next week
	std::atomic_int skippedWeeks; // no. of weeks skipped ** atomic for thread safe
	WeekLayoutManager weekLayoutManager(this);

	void goToNextWeek();
public:
	// constructor
	WeekManager();

	// getter
	int getWeek() const;

	bool isSkippedWeek() const;

	// methods

	// user manually skip to next week
	void skipToNextWeek();

	// system automatically proceed to next week after last enemy die
	void prepareForNextWeek();
};

#endif // WEEKMANAGER_H
