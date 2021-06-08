#include "camera.hpp"

eng::Camera::Camera(int x, int y) {
    v.x = x;
    v.y = y;
}

void eng::Camera::setX(int x) {
    v.x=x;
}

void eng::Camera::setY(int y) {
    v.y=y;
}

int eng::Camera::getX() {
    return v.x;
}

int eng::Camera::getY() {
    return v.y;
}
