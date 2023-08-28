#include "Snake.h"

int a;

Snake::Snake(sf::Vector2f startPosition) {
    section.setSize(sf::Vector2f(20, 20));
    switch (a) {
        case 0:
            section.setFillColor(sf::Color::Green);
            break;
        case 1:
            section.setFillColor(sf::Color::Red);
            break;
        case 2:
            section.setFillColor(sf::Color::Blue);
            break;
        case 3:
            section.setFillColor(sf::Color::Yellow);
            break;
        default:
            section.setFillColor(sf::Color::Green);
            break;
    }
    //section.setFillColor(Color::Green);
    section.setPosition(startPosition);
    position = startPosition;
}

void Snake::snakeColor(int b) {
    ::a = b;
}

sf::Vector2f Snake::getPosition() {
    return position;
}

void Snake::setPosition(sf::Vector2f newPosition) {
    position = newPosition;
}

sf::RectangleShape Snake::getShape() {
    return section;
}

void Snake::update() {
    section.setPosition(position);
}
