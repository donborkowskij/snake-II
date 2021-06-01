//
// Created by donat on 5/30/2021.
//

#ifndef FIRSTPROG_APPLE_H
#define FIRSTPROG_APPLE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Apple {
private:
    RectangleShape sprite;

public:
    Apple();

    void setPosition(Vector2f newPosition);
    RectangleShape getSprite();

};


#endif //FIRSTPROG_APPLE_H
