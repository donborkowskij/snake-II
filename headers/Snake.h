#pragma once

#include <SFML/Graphics.hpp>


class Snake {
public:
    explicit Snake(sf::Vector2f startPosition);

    static void snakeColor(int a);

    sf::RectangleShape getShape();

    sf::Vector2f getPosition();

    void setPosition(sf::Vector2f newPosition);

    void update();

private:
    sf::Vector2f position;
    sf::RectangleShape section;
};
