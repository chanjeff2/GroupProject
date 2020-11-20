#include "GPAManager.h"

// constructor
GPAManager::GPAManager() {}

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
		return true; // game over
	} else {
		return false;
	}
}
