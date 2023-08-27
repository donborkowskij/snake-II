#pragma once

#include <SFML/Graphics.hpp>
#include "MainMenu.h"

class Achievements {
public:
    void color(int i);
    void menu();
    void runMenu();
    void achievementsRun();
    void screen(sf::RenderWindow &window, int i);
    void dataHandling();
    void brain();

private:
    sf::Font font;
    int ShopSelect;
    //Change this if you add more elements.
    sf::Text AchiveText[16];
    sf::Text TextChild[16];
    sf::Text ExtraText[3];
};
