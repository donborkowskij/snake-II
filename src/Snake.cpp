#include "Snake.h"

int a;

Snake::Snake(Vector2f startPosition) {
    section.setSize(Vector2f(20, 20));
    switch (a) {
        case 0:
            section.setFillColor(Color::Green);
            break;
        case 1:
            section.setFillColor(Color::Red);
            break;
        case 2:
            section.setFillColor(Color::Blue);
            break;
        case 3:
            section.setFillColor(Color::Yellow);
            break;
        default:
            section.setFillColor(Color::Green);
            break;
    }
    //section.setFillColor(Color::Green);
    section.setPosition(startPosition);
    position = startPosition;
}

void Snake::snakeColor(int b) {
    ::a = b;
}

Vector2f Snake::getPosition() {
    return position;
}

void Snake::setPosition(Vector2f newPosition) {
    position = newPosition;
}

RectangleShape Snake::getShape() {
    return section;
}

void Snake::update() {
    section.setPosition(position);
}
