#include "tickcounter.h"

#ifdef NULL
#undef NULL
#endif
#define NULL nullptr

using namespace burbokop;

TickCounter::TickCounter() {
    this->timer = new Timer(1000);
    this->ticks = 0;
    this->tps = 0;
}

int TickCounter::count() {
    if(this->timer->count()) {
        this->tps = this->ticks;
        this->ticks = 0;
    }
    this->ticks++;
    return this->tps;
}
