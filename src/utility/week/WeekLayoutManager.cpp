#include "WeekManager.h"
#include "WeekLayoutManager.h"
#include "src/utility/GameValues.h"

WeekLayoutManager::WeekLayoutManager(WeekManager *weekManager) : weekManager(weekManager) {}

void WeekLayoutManager::isWeekCoolDown(bool isWeekCD) {
    SkipWeek->setEnabled(isWeekCD);
}

void WeekLayoutManager::weekCountDown(int time) {
    // psudo
	if (time <= 0 || isSkipped) {
		isSkipped = false;
        TimeLeft->setText("Time left: Start");
        TimeLeft->setEnabled(false);
        return;
    }

    // update time
    TimeLeft->setEnabled(true);
    TimeLeft->setText("Time left: " + QString::number(time));

    // queue for update time
	QTimer::singleShot(1000 / GAME_SPEED, [=] {
        weekCountDown(time - 1);
		});
}

void WeekLayoutManager::updateWeek(const int week) {
        WeekCount->setText("Week " + QString::number(week));
        // Update progress bar
        WeekProgress->setValue(week);
}

void WeekLayoutManager::initNumOfWeeks(int numOfWeeks) {
    WeekProgress->setMaximum(numOfWeeks);
}
