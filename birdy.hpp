#pragma once
#include "engine/engine.hpp"
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <vector>
#include <random>

class birdy : public eng::GameLogic {
public:
    void init() override {
        birdSprite = eng::Sprite::load("wall.png", 75, 75, 50, 50);
        wallSprite = eng::Sprite::load("bird.png", 50, 50, 0, 0);
        jungleSprite = eng::Sprite::load("jungle.png",1280,720,0,0);

        gravity.y = 7;
        velocity.y = 5;
        counter = 0;
    }
    void update(eng::Input &input) override {
        static double time = al_get_time();
        
        if (al_get_time()-time >= 0.3) {
            time = al_get_time();
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distr(50, 670);
            walls.push_back(eng::Vector<int>(1280,distr(gen)));
        }
        static bool prevstate = false;
        if (input.keystates[ALLEGRO_KEY_SPACE]) {
            if (prevstate == false) {
                velocity.y = 0;
                velocity.y-= 20;
            }
            prevstate = true;
        } else {
            prevstate = false;
        }
        velocity.y+=60*input.deltaTime;
        velocity.y = std::min(20, velocity.y);
        birdSprite->moveY(velocity.y);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        jungleSprite->draw();
        birdSprite->draw();

        for (int i = 0; i < walls.size();i++) {
            if (walls[i].x < -50) {
                walls.erase(walls.begin()+i);
                counter++;
            }
            walls[i].x -= 1000  * input.deltaTime;
            wallSprite->setX(walls[i].x);
            wallSprite->setY(walls[i].y);
            wallSprite->draw();
        }
        if (birdSprite->getY() > 780) {
            std::cout << counter << " Obstacles dodged." << std::endl;
            std::cout << "Survived for " << al_get_time() << "seconds." << std::endl;
            std::exit(0);
        }
        for (int i = 0; i < walls.size();i++) {
            if (birdSprite->getX() + birdSprite->getW() > walls[i].x && birdSprite->getX() < walls[i].x+50 && birdSprite->getY() + birdSprite->getH() > walls[i].y && birdSprite->getY()<walls[i].y +50) {
                std::cout << counter << " Obstacles dodged." << std::endl;
                std::cout << "Survived for " << (int) al_get_time() << " seconds." << std::endl;
                std::exit(0);
            }
        }
    }
    void exit() override {
        delete birdSprite;
    }

private:
    eng::Sprite *birdSprite;
    eng::Sprite *jungleSprite;
    eng::Sprite *wallSprite;
    eng::Vector<int> velocity;
    eng::Vector<int> gravity;
    int counter;
    std::vector<eng::Vector<int>>walls;
};
