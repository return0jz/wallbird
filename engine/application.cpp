#include "application.hpp"
#include <algorithm>

eng::GameApplication::GameApplication(GameLogic &gl, int w, int h, unsigned int refrate) {
    al_init();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    this->window = al_create_display(w, h);
    this->eventqueue = al_create_event_queue();
    if (refrate!=0){
        this->timer = al_create_timer(1.0 / refrate);
    } else {
        this->timer = al_create_timer(1.0 / 60.0);
    }
    //al_hide_mouse_cursor(this->window);
    al_register_event_source(eventqueue, al_get_keyboard_event_source());
    al_register_event_source(eventqueue, al_get_display_event_source(window));
    al_register_event_source(eventqueue, al_get_timer_event_source(timer));
    al_register_event_source(eventqueue, al_get_mouse_event_source());
    
    input.window.w = w;
    input.window.h = h;
    memset(input.keystates, 0, sizeof(input.keystates));
    memset(input.mouse.buttonstates, 0, sizeof(input.mouse.buttonstates));
    this->isRunning = true;
    this->m_gl = &gl;
    this->m_gl->init();
    
    al_start_timer(timer);
}

eng::GameApplication::~GameApplication() {
    m_gl->exit();
    al_destroy_display(window);
    al_stop_timer(timer);
    al_destroy_timer(timer);
    al_destroy_event_queue(eventqueue);
    al_uninstall_keyboard();
}

void eng::GameApplication::run() {
    while(this->isRunning) {
        ALLEGRO_EVENT event;
        al_wait_for_event(this->eventqueue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                this->isRunning = false;
                break;
                // Keyboard events
            case ALLEGRO_EVENT_KEY_DOWN:
                input.keystates[event.keyboard.keycode] = true;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                input.keystates[event.keyboard.keycode] = false;
                break;
                // Mouse events
            case ALLEGRO_EVENT_MOUSE_AXES:
                input.mouse.x = event.mouse.x;
                input.mouse.y = event.mouse.y;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                input.mouse.x = event.mouse.x;
                input.mouse.y = event.mouse.y;
                input.mouse.buttonstates[std::min(event.mouse.button-1,(unsigned int)1)] = true;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                input.mouse.x = event.mouse.x;
                input.mouse.y = event.mouse.y;
                input.mouse.buttonstates[std::min(event.mouse.button-1,(unsigned int)1)] = false;
                break;
                // Window events
            case ALLEGRO_EVENT_TIMER:
                if (al_is_event_queue_empty(eventqueue)) { // Input will be scuffed without this line. (some issue with VSYNC on my mac)
                    static double prevTime=0;
                    m_gl->update(this->input);
                    al_flip_display();
                    static double currentTime=0;
                    currentTime = al_get_time();
                    input.deltaTime = currentTime-prevTime;
                    prevTime = currentTime;
                }
                break;
        }
    }
}

