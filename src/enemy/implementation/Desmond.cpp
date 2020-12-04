#include "Desmond.h"
#include "src/utility/GameValues.h"
#include "src/utility/enemy/EnemyUtility.h"
#include <QDebug>

Desmond::Desmond(EnemyUtility *enemyUtility, Path path): IEnemy(enemyUtility, path, EnemyType::Desmond)
{
    HP = 1000;
    speed = 2.4;
    worth = 9;
	armor = 6;
	canSlow = true;
	canPierceArmor = true;
	canEnrage = true;
}
void Desmond::die() {
    this->timer->stop();
    this->enemyUtility->generateEnemyAt( EnemyType::PA , this->path );
    // notify all tower focusing this enemy to clear focus
    focusManager.requestUpdateFocus();
    // clear path to place safe
    this->path.clear();
    // delete
    this->deleteLater();
}
