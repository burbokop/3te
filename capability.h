#ifndef CAPABILITY_H
#define CAPABILITY_H


#include <SDL2/SDL.h>

namespace burbokop {

class Capability
{
protected:
    void *parent;
public:
    Capability(void *parent);
    virtual void render() = 0;
    virtual void render(SDL_Surface surface) = 0;
    virtual void action() = 0;
    virtual void event(SDL_Event *event) = 0;
};
}

#endif // CAPABILITY_H
