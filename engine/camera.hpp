#pragma once
#include "vector.hpp"
namespace eng {
class Camera {
public:
    Camera(int x, int y);
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
private:
    Vector<int> v;
};
}
