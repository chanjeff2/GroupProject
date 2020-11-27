#include "WeekManager.h"
#include "WeekLayoutManager.h"

WeekLayoutManager::WeekLayoutManager(WeekManager *weekManager) : weekManager(weekManager) {}

void WeekLayoutManager::isWeekCoolDown(bool isWeekCD) {
    SkipWeek->setEnabled(isWeekCD);
}

void WeekLayoutManager::weekCountDown(int time) {
    // psudo
    if (time <= 0 || weekManager->isSkippedWeek()) {
        TimeLeft->setEnabled(false);
        return;
    }

    // update time
    TimeLeft->setEnabled(true);
    TimeLeft->setText("Time left: " + QString::number(time));

    // queue for update time
	QTimer::singleShot(1000, [=] {
        weekCountDown(time - 1);
		});
}

void WeekLayoutManager::updateWeek(const int week) {
        WeekCount->setText("Week " + QString::number(week));
        // Update progress bar
        WeekProgress->setValue(week);
}
