#pragma once
#include "input.hpp"
namespace eng {
class GameLogic {
public:
    virtual void init() {}
    virtual void update(eng::Input &input) {}
    virtual void exit() {}
};
}
