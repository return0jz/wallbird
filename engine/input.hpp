#pragma once
#include <allegro5/allegro.h>
#include "application.hpp"

namespace eng {
class Input {
public:
    bool keystates[ALLEGRO_KEY_MAX];
    struct mouseStruct {
        int x;
        int y;
        bool buttonstates[2];
    };
    mouseStruct mouse;
    double deltaTime;
    friend class GameApplication;
    struct windowStruct {
        int w;
        int h;
    };
    windowStruct window;
};
}
