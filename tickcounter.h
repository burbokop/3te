#ifndef TICKCOUNTER_H
#define TICKCOUNTER_H

#include "timer.h"

namespace burbokop {

class TickCounter
{
private:
    Timer *timer;
    int ticks;
    int tps;

public:
    TickCounter();
    int count();
};
}
#endif // TICKCOUNTER_H
