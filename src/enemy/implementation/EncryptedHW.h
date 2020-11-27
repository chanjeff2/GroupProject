#ifndef ENCRYPTEDHW_H
#define ENCRYPTEDHW_H

#include "src/enemy/IEnemy.h"

class EncryptedHW : public IEnemy
{
public:
    EncryptedHW(EnemyUtility *enemyUtility, Path path);
};

#endif // ENCRYPTEDHW_H
