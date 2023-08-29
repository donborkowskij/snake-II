#pragma once

#include <SFML/Graphics.hpp>
#include "iostream"
#include <fstream>


class Snake {
public:
    explicit Snake(sf::Vector2f startPosition);

    void setPosition(sf::Vector2f newPosition);

    void update();

    sf::RectangleShape getShape();

    sf::Vector2f getPosition();

private:
    static void loadSnakeColor(sf::RectangleShape &section);
    sf::Vector2f position;
    sf::RectangleShape section;
};
