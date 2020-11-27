#ifndef GPAMANAGER_H
#define GPAMANAGER_H

#include "GPALayoutManager.h"

class GPAManager
{
	float gpa; // score
    GPALayoutManager* gpaLayoutManager;

public:
	GPAManager();

	// methods
	float getGPA() const;

	/* GameOver -> true
	 * GameContinue -> false
	 * usage: if (reduceGPA(amount)) [GG] */
	bool reduceGPA(float amount);
    GPALayoutManager* accessToLayoutManager() const;
};

#endif // GPAMANAGER_H

