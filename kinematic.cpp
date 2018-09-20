#include "kinematic.h"

using namespace burbokop;

Kinematic::Kinematic()
{
    this->position = new Vector();
    this->velocity = new Vector();
    this->acceleration = new Vector();
}

Kinematic::Kinematic(Vector *position)
{
    this->position = position;
    this->velocity = new Vector();
    this->acceleration = new Vector();
}

void Kinematic::applyTransformation()
{
    this->velocity = this->velocity->add(this->acceleration);
    this->position = this->position->add(this->velocity);
}

void Kinematic::applyTransformation(int c)
{
    this->velocity = this->velocity->relativisticAddition(this->acceleration, c);
    this->position = this->position->add(this->velocity);
}
