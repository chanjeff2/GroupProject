#ifndef WEEKLAYOUTMANAGER_H
#define WEEKLAYOUTMANAGER_H

#include <QString>
#include <vector>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include "src/utility/GameValues.h"
#include "src/utility/WeekManager.h"

class WeekManager;

class WeekLayoutManager {

    WeekManager* weekManager;
public:
    QLabel* WeekCount;
    QLabel* TimeLeft;
    QProgressBar* WeekProgress;
    QPushButton* SkipWeek;

    WeekLayoutManager(WeekManager *weekManager);

    // toggle skip button
    void isWeekCoolDown(bool isWeekCD);

    // week count down, time in sec
    void weekCountDown(int time);

    void updateWeek(const int week);
};

#endif // WEEKLAYOUTMANAGER_H
