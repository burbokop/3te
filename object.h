#ifndef OBJECT_H
#define OBJECT_H

#include "capability.h"

#include <vector>


namespace burbokop {

class Object
{
private:
    std::vector<Capability> *capabilities;
public:
    Object();

};
}

#endif // OBJECT_H
