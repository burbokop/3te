#include "frame.h"

#include "tickcounter.h"

using namespace burbokop::tte;

void Frame::mwl()
{
    this->initGame();
    TickCounter *tickCounter = new TickCounter();
    while (!this->exitFlag) {
        if(!this->pauseFlag) {
            this->gameLoop();
        }
        this->mwltps = tickCounter->count();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 24));
    }
}

void burbokop::tte::Frame::gwl()
{
    this->initGraphics();
    TickCounter *tickCounter = new TickCounter();
    while (!this->exitFlag) {
        this->render();
        this->gwltps = tickCounter->count();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }
}

void burbokop::tte::Frame::ewl()
{
    TickCounter *tickCounter = new TickCounter();
    while (!this->exitFlag) {
        SDL_Event event;
        if (SDL_WaitEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                this->exitFlag = true;
            }
            else if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.scancode == SDL_SCANCODE_F12) exitFlag = true;
                if(event.key.keysym.scancode == SDL_SCANCODE_F1 || event.key.keysym.scancode == SDL_SCANCODE_F2) pauseFlag = false;
            }
            else if(event.type == SDL_KEYUP) {
                if(event.key.keysym.scancode == SDL_SCANCODE_F2) pauseFlag = true;
            }
            else if(event.type == SDL_MOUSEMOTION) {
                this->mouse = new Vector(event.motion.x, event.motion.y);
            }

            this->handleEvent(&event);
        }
        this->ewltps = tickCounter->count();
    }
}

burbokop::tte::Frame::Frame()
{
    this->exitFlag = false;
    this->pauseFlag = false;

    this->mouse = new Vector();
    this->resolution = new Vector(8, 8);

    this->mwltps = -1;
    this->gwltps = -1;
    this->ewltps = -1;

    this->window = NULL;
    this->screen = NULL;

    this->fonts = new std::map<std::string, TTF_Font*>();

    this->mwlt = NULL;
    this->gwlt = NULL;
    this->ewlt = NULL;
}

void burbokop::tte::Frame::startAll()
{
    this->mwlt = new std::thread(&Frame::mwl, this);
    this->gwlt = new std::thread(&Frame::gwl, this);
    this->ewlt = new std::thread(&Frame::ewl, this);

    this->ewlt->join();
    this->gwlt->join();
    this->mwlt->join();
}

void burbokop::tte::Frame::startMainThread()
{
    if(this->mwlt == NULL) {
        this->mwlt = new std::thread(&Frame::mwl, this);
    }
}

void burbokop::tte::Frame::startGraphics()
{
    if(this->gwlt == NULL) {
        this->gwlt = new std::thread(&Frame::gwl, this);
    }
}

void burbokop::tte::Frame::startEventsHandling()
{
    if(this->ewlt == NULL) {
        this->ewlt = new std::thread(&Frame::ewl, this);
    }
}

void burbokop::tte::Frame::join()
{
    if(this->ewlt != NULL) this->ewlt->join();
    if(this->gwlt != NULL) this->gwlt->join();
    if(this->mwlt != NULL) this->mwlt->join();
}
