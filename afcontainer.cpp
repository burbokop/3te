#include "afcontainer.h"

#include <math.h>

using namespace burbokop;

double AFContainer::modmin(double a, double b)
{
    if(std::abs(a) <= std::abs(b)) return a;
    return b;
}

double AFContainer::modmax(double a, double b)
{
    if(std::abs(a) <= std::abs(b)) return b;
    return a;
}
