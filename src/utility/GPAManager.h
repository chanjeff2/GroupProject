#ifndef GPAMANAGER_H
#define GPAMANAGER_H

class GPAManager
{
	float gpa; // score

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

