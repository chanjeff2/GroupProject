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

	enum class GameStatus {
		GameOver, GameContinue, GameNotStarted
	};

	// methods
	float getGPA() const;

	/* GameOver (GPA reaches 0) -> GameStatus::GameOver
	 * GameContinue (GPA not reaches 0) -> GameStatus::GameContinue
	 * GameNotStarted -> GameStatus::GameNotStarted
	 * usage: if (reduceGPA(amount) == GameStatus::GameOver) [GG] */
	GameStatus reduceGPA(float amount);

	void setLayoutManager(GPALayoutManager* gpaLayoutManager);

    void toggle_game_started(bool game_started);
    void manager_reset();

signals:
    void game_over();
};

#endif // GPAMANAGER_H

