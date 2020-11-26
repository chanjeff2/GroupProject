#ifndef GPAMANAGER_H
#define GPAMANAGER_H

#include "GPALayoutManager.h"

class GPAManager
{
	float gpa; // score
    GPALayoutManager gpaLayoutManager{this};

public:
	GPAManager();

	// methods
	float getGPA() const;

    GPALayoutManager* accessToLayoutManager();

	/* GameOver -> true
	 * GameContinue -> false
	 * usage: if (reduceGPA(amount)) [GG] */
	bool reduceGPA(float amount);
};

#endif // GPAMANAGER_H

