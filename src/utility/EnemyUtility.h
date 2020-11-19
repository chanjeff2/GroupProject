#ifndef ENEMYUTILITY_H
#define ENEMYUTILITY_H

#include <set>
using namespace std;

#include "GameValues.h"

// forward declaration
class IEnemy;

class EnemyUtility
{
public:
	set<IEnemy*> enemies; // all enemies

		~EnemyUtility() {
			for (IEnemy *enemy: enemies) {
				delete enemy;
			}
		}

		void generateEnemy(EnemyType enemyType) {
			switch(enemyType) {
//				case EnemyType::Foo:
//					 enemies.insert(new Foo(position));
//					 break;
//				case EnemyType::Bar:
//					 enemies.insert(new Bar(position));
//					 break;
//				...
			}
		}

		void killEnemy(IEnemy* enemy) {
			// find &enemy in ememies and remove
			enemies.erase(enemy);

			delete enemy;

			// check if any remaining enemy
			if (/*no more enemy remain*/true || /*no more enemy to spawn*/ true) {
			// proceed to next week or end game
//				prepareForNextWeek()
			}
		}
};

#endif // ENEMYUTILITY_H
