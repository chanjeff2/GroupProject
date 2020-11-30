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
	// Rounding off to 1 d.p.
	int temp = gpa * 10 + 0.5;
	gpa = temp / 10.0;

	if (gpa <= 0) {
        gpa = 0.0;
		gpaLayoutManager->UpdateGPA(gpa);
		return true; // game over
	} else {
		gpaLayoutManager->UpdateGPA(gpa);
		return false;
	}
}

void GPAManager::setLayoutManager(GPALayoutManager* gpaLayoutManager) {
	this->gpaLayoutManager = gpaLayoutManager;
}
