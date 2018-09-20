#ifndef FRAME_H
#define FRAME_H

#include "vector.h"

#include <SDL2/SDL_ttf.h>
#include <thread>
#include <map>

namespace burbokop {
namespace tte {

class Frame
{
private:
    std::thread *mwlt;
    std::thread *gwlt;
    std::thread *ewlt;

    void mwl();
    void gwl();
    void ewl();
protected:
    bool exitFlag;
    bool pauseFlag;

    Vector *mouse;
    Vector *resolution;
    SDL_Window *window;
    SDL_Surface *screen;

    std::map<std::string, TTF_Font*> *fonts;

    int mwltps;
    int gwltps;
    int ewltps;

    virtual void gameLoop() = 0;
    virtual void initGame() = 0;
    virtual void initGraphics() = 0;
    virtual void render() = 0;
    virtual void handleEvent(SDL_Event *event) = 0;
public:
    Frame();
    void startAll();
    void startMainThread();
    void startGraphics();
    void startEventsHandling();
    void join();
};
}
}



#endif // FRAME_H
