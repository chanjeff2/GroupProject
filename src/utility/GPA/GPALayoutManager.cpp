#include "GPALayoutManager.h"
#include "GPAManager.h"

GPALayoutManager::GPALayoutManager(GPAManager* gpaManager) : gpaManager(gpaManager) {}

void GPALayoutManager::UpdateGPA(float GPA) {
    QString grade;
    // Get what grade it is now actually
    if (GPA == MAX_GPA) grade = grades[0];
    else if (GPA >= 4.0 && GPA < 4.3) grade = grades[1];
    else if (GPA >= 3.7 && GPA < 4.0) grade = grades[2];
    else if (GPA >= 3.3 && GPA < 3.7) grade = grades[3];
    else if (GPA >= 3.0 && GPA < 3.3) grade = grades[4];
    else if (GPA >= 2.7 && GPA < 3.0) grade = grades[5];
    else if (GPA >= 2.3 && GPA < 2.7) grade = grades[6];
    else if (GPA >= 2.0 && GPA < 2.3) grade = grades[7];
    else if (GPA >= 1.7 && GPA < 2.0) grade = grades[8];
    else if (GPA >= 1.0 && GPA < 1.7) grade = grades[9];
    else grade = grades[10];
    GPALabel->setText(QString::number(GPA));
    GradeLabel->setText("(" + grade + ")");

    // Your GPA Blinks if it drops
    GPALabel->setStyleSheet(QStringLiteral("QLabel{color: rgb(255, 0, 0);}"));
    QTimer::singleShot(100, [&]{
        GPALabel->setStyleSheet(QStringLiteral("QLabel{color: rgb(0, 0, 0);}"));
    });
}
