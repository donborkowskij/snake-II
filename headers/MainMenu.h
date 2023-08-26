#pragma once

#include <SFML/Graphics.hpp>
#include "Engine.h"

//Edit if you want to add more elements
#define MENU_ELEMENTS 4


class MainMenu {
public:
    explicit MainMenu(sf::RenderWindow& window);
    void menuRun(RenderWindow& window);

private:
    int mainMenuSelect;
    sf::Font font;
    sf::Text mainMenu[MENU_ELEMENTS];
    void moveUp();
    void moveDown();
    void draw(sf::RenderWindow &window);
    void runSnake();
    void runShop();
    void runAchievements();
};
