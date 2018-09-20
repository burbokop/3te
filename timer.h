#ifndef TIMER_H
#define TIMER_H

#include <sys/timeb.h>

namespace burbokop {

class Timer
{
private:
    long interval;
    long duration;
    long getMilliseconds();

public:
    Timer(long interval);
    bool count();
    void reset();
};
}
#endif // TIMER_H
