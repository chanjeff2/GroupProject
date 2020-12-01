#include "GPAManager.h"
#include "GPALayoutManager.h"
#include "src/utility/GameValues.h"

#include <QDebug>

// constructor
GPAManager::GPAManager(): gpa(MAX_GPA) {}

// methods
float GPAManager::getGPA() const {
	return gpa;
}

/* GameOver -> true
		 * GameContinue -> false
		 * usage: if (reduceGPA(amount)) [GG] */

bool GPAManager::reduceGPA(float amount) {
	qDebug() << "GPAManager: reduce GPA, amount:" << amount;
	gpa -= amount;
	// Rounding off to 1 d.p.
	int temp = gpa * 10 + 0.5;
	gpa = temp / 10.0;

	if (gpa <= 0) {
        gpa = 0.0;
		gpaLayoutManager->UpdateGPA(gpa);
		qDebug() << "GPAManager: new GPA:" << gpa;
        if (!is_game_over) {
            is_game_over = true;
            qDebug() << "Game Over!";
            emit game_over();
        }
		return true; // game over
	} else {
		gpaLayoutManager->UpdateGPA(gpa);
		qDebug() << "GPAManager: new GPA:" << gpa;
		return false;
	}
}

void GPAManager::setLayoutManager(GPALayoutManager* gpaLayoutManager) {
	this->gpaLayoutManager = gpaLayoutManager;
}
