
#include <iostream>
#include "rigidbody.h"

#ifdef NULL
#undef NULL
#endif
#define NULL nullptr

using namespace burbokop;


Rigidbody::Rigidbody(Vector *position, int mass, int radius, bool fixed) : Kinematic(position)
{
    this->mass = mass;
    this->radius = radius;
    this->fixed = fixed;
}

int Rigidbody::getMass()
{
    return this->mass;
}

Vector *Rigidbody::getPosition()
{
    return this->position;
}

void Rigidbody::fall(std::vector<Rigidbody *> *masses)
{
    int n = 0, m = 0, j = 0;
    for (Rigidbody *mass : *masses) {
        if (mass != this) {
            std::cout << "not this\n";
            n += mass->getPosition()->getDoubleX() * mass->getMass();
            m += mass->getPosition()->getDoubleY() * mass->getMass();
            j += mass->getMass();
        }
        else {
            std::cout << "this\n";
        }
    }

    Vector *center = this->position->subtract(new Vector(n / j, m / j));

    double gravity = ((j * GRAVITY_CONSTANT) / pow(center->module(), 2));

    this->acceleration = center->normalized()->multiply(-gravity);
}

/*
void Rigidbody::collision(std::vector<Rigidbody *> *colliders)
{
    for (Rigidbody *colider : *colliders) {
        if (colider != this) {
            if(this->position->add(this->velocity)->subtract(colider->position)->module() <= this->shape->getSize() + colider->shape->getSize()) {
                //this->acceleration = this->position->subtract(colider->position)->multiply(colider->getMass() / this->mass * 0.1);

                Vector *normal = this->position->add(this->velocity)->subtract(colider->position)->normalized();
                debug = normal;
                debug2 = this->velocity->subtract(normal->multiply(normal->scalarProduct(this->velocity) * 2));

                this->velocity = this->velocity->subtract(normal->multiply(normal->scalarProduct(this->velocity) * 2));


                //r=d−2 (d⋅n) n
            }
        }
        else {
            std::cout << "this colider\n";
        }
    }
}

void Rigidbody::borderCollision(Vector *begin, Vector *end)
{
    if(this->position->x - this->shape->getSize() / 2 <= begin->getIntX()) this->velocity->x = abs(this->velocity->x);
    else if(this->position->x + this->shape->getSize() / 2 >= end->getIntX()) this->velocity->x = -abs(this->velocity->x);

    if(this->position->y - this->shape->getSize() / 2 <= begin->getIntY()) this->velocity->y = abs(this->velocity->y);
    else if(this->position->y + this->shape->getSize() / 2 >= end->getIntY()) this->velocity->y = -abs(this->velocity->y);
}
*/
