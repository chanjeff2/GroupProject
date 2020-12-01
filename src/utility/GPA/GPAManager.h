#ifndef GPAMANAGER_H
#define GPAMANAGER_H

#include <QObject>
#include "GPALayoutManager.h"

class GPAManager : public QObject
{
    Q_OBJECT

private:
	float gpa; // score
    GPALayoutManager* gpaLayoutManager;
    bool is_game_over;

public:
	GPAManager();

	// methods
	float getGPA() const;

	/* GameOver -> true
	 * GameContinue -> false
	 * usage: if (reduceGPA(amount)) [GG] */
	bool reduceGPA(float amount);

	void setLayoutManager(GPALayoutManager* gpaLayoutManager);

signals:
    void game_over();
};

#endif // GPAMANAGER_H

