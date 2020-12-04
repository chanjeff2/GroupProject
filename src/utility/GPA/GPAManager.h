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
    bool is_game_over {false};
    bool is_game_started {false};

public:
	GPAManager();

	// methods
	float getGPA() const;

	/* GameOver -> true
	 * GameContinue -> false
	 * usage: if (reduceGPA(amount)) [GG] */
    bool reduceGPA(float amount); // returns true if GPA reaches 0

	void setLayoutManager(GPALayoutManager* gpaLayoutManager);

    void toggle_game_started(bool game_started);
    void manager_reset();

signals:
    void game_over();
};

#endif // GPAMANAGER_H

