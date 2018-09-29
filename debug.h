#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>
#include <SDL2/SDL.h>


namespace burbokop {
class Debug
{
private:
    static bool logFlag;
    static char *logFile;
public:
    static void enableLog();
    static void enableLog(char *path);
    static void disableLog();
    static void log(const std::string text);
    void shotImage(SDL_Surface *image);
};
}
#endif // DEBUG_H
