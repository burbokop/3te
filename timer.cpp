#include "timer.h"

#ifdef NULL
#undef NULL
#endif
#define NULL nullptr

using namespace burbokop;

Timer::Timer(long interval)
{
    this->interval = interval;
    this->duration = 0;
}

bool Timer::count() {
    if (this->getMilliseconds() - this->duration > this->interval) {
        this->duration = this->getMilliseconds();
        return true;
    }
    else return false;
}

void Timer::reset()
{
    this->duration = this->getMilliseconds();
}

long Timer::getMilliseconds(){
    timeb tb;
    ftime(&tb);
    int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
    return nCount;
}
