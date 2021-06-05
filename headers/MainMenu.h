//
// Created by marki on 2021-06-02.
//

#ifndef FIRSTPROG_MAINMENU_H
#define FIRSTPROG_MAINMENU_H

#include <SFML/Graphics.hpp>
#include "Engine.h"

//Edit if you want to add more elements
#define max_main_menu 4


class MainMenu {
    private:
        int mainMenuSelect;
        sf::Font font;
        sf::Text mainMenu[max_main_menu];
    public:
        void Menu();

        void Draw(sf::RenderWindow &window);
        void moveUp();
        void moveDown();

        //ToDo: Add move Main Menu navigation options (?)
        //void moveLeft();
        //void moveRight();
        void MenuRun();
        void RunSnake();
        void RunShop();
        void RunAchievements();


    //void runMenu();
};


#endif //FIRSTPROG_MAINMENU_H
