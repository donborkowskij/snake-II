#pragma once

#include <SFML/Graphics.hpp>


class Wall {
public:
    Wall(sf::Vector2f position, sf::Vector2f size);

    sf::RectangleShape getShape();

private:
    sf::RectangleShape wallShape;
};
