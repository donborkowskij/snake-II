#pragma once

#include <SFML/Graphics.hpp>

class Apple {
public:
    Apple();

    void setPosition(sf::Vector2f newPosition);

    sf::RectangleShape getSprite();

private:
    sf::RectangleShape mSprite;
};
