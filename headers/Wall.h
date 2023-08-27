#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Wall {
public:
    Wall(Vector2f position, Vector2f size);
    RectangleShape getShape();

private:
    RectangleShape wallShape;
};
