#ifndef MATHEXAM_H
#define MATHEXAM_H

#include "IEnemy.h"

class MATHExam : public IEnemy
{
public:
    MATHExam(EnemyUtility *enemyUtility, Path path);
};

#endif // MATHEXAM_H
