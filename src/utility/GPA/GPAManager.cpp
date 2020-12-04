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

/* GameOver -> GameStatus::GameOver
 * GameContinue -> GameStatus::GameContinue
 * GameNotStarted -> GameStatus::GameNotStarted
 * usage: if (reduceGPA(amount) == GameStatus::GameOver) [GG] */
GPAManager::GameStatus GPAManager::reduceGPA(float amount) {
	if (!is_game_started)
		return GameStatus::GameNotStarted;

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
		return GameStatus::GameOver; // game over
	} else {
		gpaLayoutManager->UpdateGPA(gpa);
		qDebug() << "GPAManager: new GPA:" << gpa;
		return GameStatus::GameContinue;
	}
}

void GPAManager::setLayoutManager(GPALayoutManager* gpaLayoutManager) {
	this->gpaLayoutManager = gpaLayoutManager;
}

void GPAManager::manager_reset() {
    gpa = MAX_GPA;
    is_game_over = false;
    is_game_started = false;
    gpaLayoutManager->UpdateGPA(gpa);
}

void GPAManager::toggle_game_started(bool game_started) {
    is_game_started = game_started;
}
