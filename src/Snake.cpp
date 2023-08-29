#include "Snake.h"

Snake::Snake(sf::Vector2f startPosition) {
    section.setSize(sf::Vector2f(20, 20));
    section.setPosition(startPosition);
    loadSnakeColor(section);
    position = startPosition;
}

void Snake::loadSnakeColor(sf::RectangleShape &section) {
    int fillColor;
    std::ifstream saveFileProfile("assets/save/Bought.txt");
    if (saveFileProfile.is_open()) {
        if (saveFileProfile >> fillColor) {
            saveFileProfile.close();
        } else {
            std::cerr << "Error reading integer from the file." << std::endl;
        }
    } else {
        std::cerr << "Could not open file for reading." << std::endl;
    }

    switch (fillColor) {
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
