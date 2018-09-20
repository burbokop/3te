#ifndef KINEMATIC_H
#define KINEMATIC_H

#include "vector.h"

#include <vector>
#include <spm.h>

namespace burbokop {

class Kinematic
{
protected:
    Vector *position;
    Vector *velocity;
    Vector *acceleration;
public:
    Kinematic();
    Kinematic(Vector *position);

    void applyTransformation();
    void applyTransformation(int c);
};
}

#endif // KINEMATIC_H
