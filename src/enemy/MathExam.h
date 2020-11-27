#ifndef MATHEXAM_H
#define MATHEXAM_H

#include "IEnemy.h"

class MathExam : public IEnemy
{
public:
    MathExam(EnemyUtility *enemyUtility, Path path);
};

#endif // MATHEXAM_H
