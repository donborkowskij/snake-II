#include "Wall.h"

Wall::Wall(sf::Vector2f position, sf::Vector2f size) {
    wallShape.setSize(size);
    wallShape.setFillColor(sf::Color::White);
    wallShape.setPosition(position);
}

sf::RectangleShape Wall::getShape() {
    return wallShape;
}
