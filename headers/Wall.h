//
// Created by donat on 5/31/2021.
//

#ifndef FIRSTPROG_WALL_H
#define FIRSTPROG_WALL_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Wall {
private:
    RectangleShape wallShape;

public:
    Wall(Vector2f position, Vector2f size);

    RectangleShape getShape();
};


#endif //FIRSTPROG_WALL_H
