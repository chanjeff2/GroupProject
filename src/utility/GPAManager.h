#ifndef GPAMANAGER_H
#define GPAMANAGER_H

#include "GameValues.h"

class GPAManager
{
	float gpa = MAX_GPA; // score

public:
	GPAManager();

	// methods
	float getGPA() const;

	/* GameOver -> true
	 * GameContinue -> false
	 * usage: if (reduceGPA(amount)) [GG] */
	bool reduceGPA(float amount);
};

#endif // GPAMANAGER_H
