#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "kinematic.h"

#define GRAVITY_CONSTANT 6,67

#define RIGIDBODY_FIXED 0
#define RIGIDBODY_FREE 0

namespace burbokop {

class Rigidbody : public Kinematic
{
private:
    int mass;
    int radius;
    bool fixed;

    void fall(std::vector<Rigidbody *> *masses);
    void collision(std::vector<Rigidbody *> *colliders);
    void borderCollision(Vector *begin, Vector *end);

public:
    Rigidbody(Vector *position, int mass, int radius, bool fixed);
    void generalProcessing();
    void generalGraphics(SDL_Surface *surface);

    int getMass();
    Vector *getPosition();

};
}

#endif // RIGIDBODY_H
