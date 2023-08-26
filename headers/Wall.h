#ifndef FIRSTPROG_WALL_H
#define FIRSTPROG_WALL_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Wall {
public:
    Wall(Vector2f position, Vector2f size);
    RectangleShape getShape();

private:
    RectangleShape wallShape;
};

#endif //FIRSTPROG_WALL_H
