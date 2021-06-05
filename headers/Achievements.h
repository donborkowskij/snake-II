//
// Created by marki on 2021-06-05.
//

#ifndef FIRSTPROG_ACHIEVEMENTS_H
#define FIRSTPROG_ACHIEVEMENTS_H

#include <SFML/Graphics.hpp>
#include "MainMenu.h"

class Achievements {
    private:
    sf::Font font;

    int ShopSelect;
    //Change this if you add more elements.
    sf::Text AchiveText[16];
    sf::Text TextChild[16];
    sf::Text ExtraText[3];

    public:
    void Color(int i);

    void Menu();
    void runMenu();
    void AchievementsRun();
    void Screen(sf::RenderWindow &window, int i);
    void DataHandling();
    void Brain();
};



#endif //FIRSTPROG_ACHIEVEMENTS_H
