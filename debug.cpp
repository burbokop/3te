#include "debug.h"

#ifdef NULL
#undef NULL
#endif
#define NULL nullptr

using namespace burbokop;

bool Debug::logFlag = false;
char *Debug::logFile = "tte.log";

void Debug::enableLog()
{
    logFlag = true;
    Debug::log("DEBUG ENABLED");
}

void Debug::enableLog(char *path)
{
    logFlag = true;
    logFile = path;
}

void Debug::disableLog()
{
    logFlag = false;
    Debug::log("DEBUG DISABLED");
}

void Debug::log(const std::string text)
{
    if(logFlag) {
        std::ofstream ofilet(logFile, std::ios::out | std::ios::app);
        ofilet << "log: " << text << "\n";
        ofilet.close();
    }
}

void Debug::shotImage(SDL_Surface *image) {
    SDL_Window *window;
    SDL_Surface *screen = nullptr;

    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("DEBUG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, image->w, image->h, 0);
    screen = SDL_GetWindowSurface(window);

    SDL_FillRect(screen, nullptr, 0xffffff);
    SDL_BlitSurface(image, nullptr, screen, nullptr);
    SDL_UpdateWindowSurface(window);

    SDL_Delay(6000);

    SDL_FreeSurface(screen);
    SDL_FreeSurface(image);
    SDL_Quit();
}
