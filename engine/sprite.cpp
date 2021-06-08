#include "sprite.hpp"
#include <iostream>

eng::Sprite* eng::Sprite::load(std::string path, int w, int h, int x, int y) {
    eng::Sprite *ptr = new Sprite();
    ALLEGRO_BITMAP *loaded;
    if (!(loaded = al_load_bitmap(path.data()))) {
        delete ptr;
        return nullptr;
    } else {
        ptr->sprite = al_create_bitmap(w, h);
        ALLEGRO_BITMAP *backbuffer = al_get_target_bitmap();
        al_set_target_bitmap(ptr->sprite);
        al_draw_scaled_bitmap(loaded, 0, 0, al_get_bitmap_width(loaded), al_get_bitmap_height(loaded), 0, 0, w, h, 0);
        ptr->v.x = x;
        ptr->v.y = y;
        ptr->v.z = w;
        ptr->v.w = h;
        al_set_target_bitmap(backbuffer);
        al_destroy_bitmap(loaded);
        return ptr;
    }
}

eng::Sprite* eng::Sprite::load(std::string path, const eng::Vector<int> &v) {
    eng::Sprite *ptr = new Sprite();
    ALLEGRO_BITMAP *loaded;
    if (!(loaded = al_load_bitmap(path.data()))) {
        delete ptr;
        return nullptr;
    } else {
        ptr->sprite = al_create_bitmap(v.z, v.w);
        ALLEGRO_BITMAP *backbuffer = al_get_target_bitmap();
        al_set_target_bitmap(ptr->sprite);
        al_draw_scaled_bitmap(loaded, 0, 0, al_get_bitmap_width(loaded), al_get_bitmap_height(loaded), 0, 0, v.z, v.w, 0);
        ptr->v.x = v.x;
        ptr->v.y = v.y;
        ptr->v.z = v.z;
        ptr->v.w = v.w;
        al_set_target_bitmap(backbuffer);
        al_destroy_bitmap(loaded);
        return ptr;
    }
}

eng::Sprite::~Sprite() {
    al_destroy_bitmap(this->sprite);
}

void eng::Sprite::draw() {
     al_draw_bitmap(this->sprite, this->v.x, this->v.y, 0);
}

void eng::Sprite::draw(eng::Camera &camera) {
    al_draw_bitmap(this->sprite, this->v.x -camera.getX(), this->v.y-camera.getY(), 0);
}

void eng::Sprite::setX(int x) {
    this->v.x = x;
}

void eng::Sprite::setY(int y) {
    this->v.y = y;
}

void eng::Sprite::moveX(int x) {
    this->v.x=this->v.x+x;
}

void eng::Sprite::moveY(int y) {
    this->v.y=this->v.y+y;
}

void eng::Sprite::set(const eng::Vector<int> &pv) {
    this->v.x = pv.x;
    this->v.y = pv.y;
}

int eng::Sprite::getX() {
    return this->v.x;
}

int eng::Sprite::getY() {
    return this->v.y;
}

int eng::Sprite::getW() {
    return this->v.z;
}

int eng::Sprite::getH() {
    return this->v.w;
}
