#pragma once
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>
#include <string>
#include "camera.hpp"
#include "vector.hpp"


namespace eng {
class Sprite {
public:
    static Sprite* load(std::string path, int w, int h, int x, int y);
    static Sprite* load(std::string path, const Vector<int> &v);
    ~Sprite();
    void draw();
    void draw(Camera &camera);
    void setX(int x);
    void setY(int y);
    void moveX(int x);
    void moveY(int y);
    void set(const Vector<int> &pv);
    int getX();
    int getY();
    int getW();
    int getH();
private:
    ALLEGRO_BITMAP *sprite;
    Vector<int> v; // z and w are width and height
};
}
