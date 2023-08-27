#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Snake {
public:
    explicit Snake(Vector2f startPosition);
    static void snakeColor(int a);
    RectangleShape getShape();
    Vector2f getPosition();
    void setPosition(Vector2f newPosition);
    void update();

private:
    Vector2f position;
    RectangleShape section;
};
