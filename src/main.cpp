#include <SFML/Graphics.hpp>
#include "MainMenu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake2");

    MainMenu menu(window);

    return 0;
}