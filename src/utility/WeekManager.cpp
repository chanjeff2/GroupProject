#include "WeekManager.h"

void WeekManager::goToNextWeek() {
	// do nothing if week haven't cooldown
	if (!isWeekCooldown) {
		return;
	}

	isWeekCooldown = false;
	weekLayoutManager.isWeekCoolDown(false);
	// goto next week
	++week;
	weekLayoutManager.updateWeek(week);

	// cooldown week skip
	QTimer::singleShot(WEEK_COOLDOWN * 1000, this, SLOT([]{
		isWeekCooldown = true
		weekLayoutManager.isWeekCoolDown(true);
	}));
//	[psudo: delayedFunction({
//		isWeekCooldown = true
//		weekLayoutManager.isWeekCoolDown(true);
//	}, WEEK_COOLDOWN * 1000)]
}

// constructor
WeekManager::WeekManager() {
	week = 0;
	isWeekCooldown = true;
	skippedWeeks = 0;
}

// getter
int WeekManager::getWeek() const {
	return week;
}

bool WeekManager::isSkippedWeek() const {
	return skippedWeeks > 0;
}

// methods

// user manually skip to next week
void WeekManager::skipToNextWeek() {
	// increment skip counter
	++skippedWeeks;

	goToNextWeek();
}

// system automatically proceed to next week after last enemy die
void WeekManager::prepareForNextWeek() {
	if (!isSkippedWeek()) {
		weekLayoutManager.weekCountDown(WEEK_COUNTDOWN)
	}
	// start count down timer to proceed to next week
	// cooldown week skip
	QTimer::singleShot(WEEK_COUNTDOWN * 1000, this, SLOT([]{
		if (!isSkippedWeek())
			goToNextWeek();
		else
			skippedWeeks--;
	}));
//	[psudo: delayedFunction({
//		if (!isSkippedWeek())
//			goToNextWeek();
//		else
//			skippedWeeks--;
//		}, WEEK_COUNTDOWN * 1000)]
}
