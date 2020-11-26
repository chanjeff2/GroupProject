#ifndef GPALAYOUTMANAGER_H
#define GPALAYOUTMANAGER_H

#include <QString>
#include <vector>
#include <QLabel>
#include "src/utility/GameValues.h"

class GPAManager;

class GPALayoutManager {
    GPAManager* gpaManager;
    const std::vector<QString> grades = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"};
public:
    QLabel* GPALabel;
    QLabel* GradeLabel;

    GPALayoutManager(GPAManager* gpaManager);

    // May need optimization
    void UpdateGPA(float GPA);
};
#endif // GPALAYOUTMANAGER_H
