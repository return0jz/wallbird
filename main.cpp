#include "engine/engine.hpp"
#include "birdy.hpp"

int main(int argc, char **argv)
{
    //mv1 mygame;
    birdy mygame;
    eng::GameApplication app(mygame, 1280, 720, 60);
    app.run();
    return 0;
}
