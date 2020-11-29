#include "GPAManager.h"
#include "GPALayoutManager.h"
#include "src/utility/GameValues.h"

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
	gpaLayoutManager->UpdateGPA(gpa);

	if (gpa <= 0) {
        gpa = 0.0;
		return true; // game over
	} else {
		return false;
	}
}

void GPAManager::setLayoutManager(GPALayoutManager* gpaLayoutManager) {
	this->gpaLayoutManager = gpaLayoutManager;
}
