#include "Apple.h"

Apple::Apple() {
    sf::Vector2f startingPosition(400, 300);
    mSprite.setSize(sf::Vector2f(20, 20));
    mSprite.setFillColor(sf::Color::Red);
    mSprite.setPosition(startingPosition);
}

void Apple::setPosition(sf::Vector2f newPosition) {
    mSprite.setPosition(newPosition);
}

sf::RectangleShape Apple::getSprite() {
    return mSprite;
}
