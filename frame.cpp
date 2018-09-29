#include "frame.h"

#include "tickcounter.h"
#include "debug.h"


#ifdef NULL
#undef NULL
#endif
#define NULL nullptr

using namespace burbokop::tte;

void Frame::mwl()
{
    Debug::log("Initializing game.");
    this->initGame();
    Debug::log("Game initialised successfully.");
    TickCounter *tickCounter = new TickCounter();
    Debug::log("Starting main loop.");
    while (!this->exitFlag) {
        //Debug::log("Beginning of main loop iteration.");
        if(!this->pauseFlag) {
            this->gameLoop();
        }
        this->mwltps = tickCounter->count();
        //Debug::log("Ending of main loop iteration (fps: " + std::to_string(this->mwltps) + ").");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 24));
    }
    Debug::log("Main loop ended.");
}

void burbokop::tte::Frame::gwl()
{
    Debug::log("Initializing graphics.");
    this->initGraphics();
    Debug::log("Graphics initialised successfully.");
    TickCounter *tickCounter = new TickCounter();
    Debug::log("Starting render loop.");
    while (!this->exitFlag) {
        //Debug::log("Beginning of render loop iteration.");
        this->render();
        this->gwltps = tickCounter->count();
        //Debug::log("Ending of render loop iteration (fps: " + std::to_string(this->gwltps) + ").");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }
    Debug::log("Render loop ended.");
}

void burbokop::tte::Frame::ewl()
{
    Debug::log("Initializing event handler.");
    TickCounter *tickCounter = new TickCounter();
    Debug::log("Event handler initialised successfully.");
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
    Debug::log("Event loop ended.");
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
