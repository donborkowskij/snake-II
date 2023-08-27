#pragma once

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
