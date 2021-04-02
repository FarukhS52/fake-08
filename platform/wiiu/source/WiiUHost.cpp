/*
Wii U port todo:
1) sound messed up (turned off)
2) Fix buttons being very confusing
*/
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
using namespace std;

#include "../../../source/host.h"
#include "../../../source/hostVmShared.h"
#include "../../../source/nibblehelpers.h"
#include "../../../source/logger.h"

// sdl
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#define WINDOW_SIZE_X 1280
#define WINDOW_SIZE_Y 720

#define JOY_A     0
#define JOY_B     1
#define JOY_X     2
#define JOY_Y     3
#define LSTICK    4
#define RSTICK    5
#define JOY_L     6
#define JOY_R     7
#define JOY_ZL    8
#define JOY_ZR    9
#define JOY_PLUS  10
#define JOY_MINUS 11
#define JOY_LEFT  12
#define JOY_UP    13
#define JOY_RIGHT 14
#define JOY_DOWN  15

#define WINDOW_FLAGS SDL_WINDOW_SHOWN

#define RENDERER_FLAGS SDL_RENDERER_ACCELERATED
#define PIXEL_FORMAT SDL_PIXELFORMAT_BGRA8888

SDL_Event event;

string _desktopSdl2SettingsDir = "fs:/vol/external01/fake08";
string _desktopSdl2SettingsPrefix = "fs:/vol/external01/fake08/";
string _desktopSdl2customBiosLua = "sd:/p8carts/\"\n"
        "pausebtn = \"+\"";


Host::Host() 
{
    struct stat st = {0};

    int res = chdir(getenv("fs:/vol/external01/"));
    if (res == 0 && stat("fake08", &st) == -1) {
        res = mkdir("fake08", 0777);
    }


    setPlatformParams(
        WINDOW_SIZE_X,
        WINDOW_SIZE_Y,
        WINDOW_FLAGS,
        RENDERER_FLAGS,
        PIXEL_FORMAT,
        _desktopSdl2SettingsPrefix,
        _desktopSdl2customBiosLua
    );

}

InputState_t Host::scanInput(){ 
    currKDown = 0;
    uint8_t kUp = 0;
    stretchKeyPressed = false;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_JOYBUTTONDOWN :
                switch (event.jbutton.button)
                {
                    case JOY_PLUS:  currKDown |= P8_KEY_PAUSE; break;
                    case JOY_LEFT:  currKDown |= P8_KEY_LEFT; break;
                    case JOY_RIGHT: currKDown |= P8_KEY_RIGHT; break;
                    case JOY_UP:    currKDown |= P8_KEY_UP; break;
                    case JOY_DOWN:  currKDown |= P8_KEY_DOWN; break;
                    case JOY_A:     currKDown |= P8_KEY_X; break;
                    case JOY_B:     currKDown |= P8_KEY_O; break;

                    case JOY_L: lDown = true; break;
                    case JOY_R: rDown = true; stretchKeyPressed = true; break;
                }
                break;

            case SDL_JOYBUTTONUP :
                switch (event.jbutton.button)
                {
                    case JOY_PLUS:  kUp |= P8_KEY_PAUSE; break;
                    case JOY_LEFT:  kUp |= P8_KEY_LEFT; break;
                    case JOY_RIGHT: kUp |= P8_KEY_RIGHT; break;
                    case JOY_UP:    kUp |= P8_KEY_UP; break;
                    case JOY_DOWN:  kUp |= P8_KEY_DOWN; break;
                    case JOY_A:     kUp |= P8_KEY_X; break;
                    case JOY_B:     kUp |= P8_KEY_O; break;

                    case JOY_L: lDown = false; break;
                    case JOY_R: rDown = false; break;
                }
               break;

            case SDL_QUIT:
                quit = 1;
                break;
        }
    }

    if (lDown && rDown){
        quit = 1;
    }

    currKHeld |= currKDown;
    currKHeld ^= kUp;

    return InputState_t {
        currKDown,
        currKHeld
    };
    
}


vector<string> Host::listcarts(){
    vector<string> carts;

    
    std::string cartDir = "p8carts";
    std::string container = "fs:/vol/external01/";
    std::string fullCartDir = container + cartDir;

    chdir(container.c_str());
    DIR* dir = opendir(cartDir.c_str());
    struct dirent *ent;
    if (dir != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            carts.push_back(fullCartDir + "/" + ent->d_name);
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
    }

    
    return carts;
}

