#pragma once

#include <SFML/Graphics.hpp>
#include "iostream"
#include <fstream>


class Snake {
public:
    explicit Snake(sf::Vector2f startPosition);

    sf::RectangleShape getShape();

    sf::Vector2f getPosition();

    void setPosition(sf::Vector2f newPosition);

    void update();

private:
    sf::Vector2f position;
    sf::RectangleShape section;

    static void loadSnakeColor(sf::RectangleShape &section);
};
