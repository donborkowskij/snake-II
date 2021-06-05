//
// Created by donat on 5/30/2021.
//

#ifndef FIRSTPROG_SNAKE_H
#define FIRSTPROG_SNAKE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Snake {
private:
    Vector2f position;
    RectangleShape section;

public:
    static void SnakeColor(int a);
    explicit Snake(Vector2f startPosition);

    Vector2f getPosition();
    void setPosition(Vector2f newPosition);

    RectangleShape getShape();

    void update();

};


#endif //FIRSTPROG_SNAKE_H
