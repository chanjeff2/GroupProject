#ifndef ENCRYPTEDHW_H
#define ENCRYPTEDHW_H

#include "IEnemy.h"

class EncryptedHW : public IEnemy
{
public:
    EncryptedHW(EnemyUtility *enemyUtility, Path path);
};

#endif // ENCRYPTEDHW_H
