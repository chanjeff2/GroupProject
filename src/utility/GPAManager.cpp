#include "GPAManager.h"
#include "GameValues.h"

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
	gpa -= amount;

	if (gpa <= 0) {
        gpa = 0.0;
		return true; // game over
	} else {
		return false;
	}
}
