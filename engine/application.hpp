#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <iostream>
#include "gamelogic.hpp"
#include "input.hpp"

namespace eng {
class GameApplication {
public:
    GameApplication(GameLogic &gl, int w, int h, unsigned int refrate); // default refresh rate is 0
    ~GameApplication();
    void run();
private:
    ALLEGRO_DISPLAY *window;
    ALLEGRO_EVENT_QUEUE *eventqueue;
    ALLEGRO_TIMER *timer;
    
    GameLogic *m_gl;
    Input input;
    bool isRunning;
    bool update;
};
}
