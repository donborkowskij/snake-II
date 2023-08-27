#pragma once

#include <SFML/Graphics.hpp>
#include "Engine.h"

//Edit if you want to add more elements
#define MENU_ELEMENTS 4


class MainMenu {
public:
    explicit MainMenu();
    void menuRun(RenderWindow &window);

private:
    int mainMenuSelect;
    sf::Font font;
    sf::Text mainMenu[MENU_ELEMENTS];
    void moveUp();
    void moveDown();
    void draw(sf::RenderWindow &window);
    static void runSnake();
    static void runShop(sf::RenderWindow& window);
    static void runAchievements();
};
