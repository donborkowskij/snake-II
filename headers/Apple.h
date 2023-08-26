#ifndef FIRSTPROG_APPLE_H
#define FIRSTPROG_APPLE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Apple {
public:
    Apple();
    void setPosition(Vector2f newPosition);
    RectangleShape getSprite();

private:
    RectangleShape sprite;
};

#endif //FIRSTPROG_APPLE_H
