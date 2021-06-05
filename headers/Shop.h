//
// Created by marki on 2021-06-04.
//

#ifndef FIRSTPROG_SHOP_H
#define FIRSTPROG_SHOP_H

#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "Snake.h"
#include <fstream>


class Shop {
private:
    int ShopSelect;
    sf::Font font;
    sf::Text MainText[4];
    sf::Text TextChild[4];
    sf::Text ExtraText[5];
    sf::Text AltText[4];

public:
    void LoadData();
    void Menu();

    void Draw(sf::RenderWindow &window);
    void DrawExtra(sf::RenderWindow &window);

    void moveUp();
    void moveDown();

    int ReturnBought(int number);
    void SaveBought(int GreenSnake, int  RedSnake, int BlueSnake, int YellowSnake);
    void SaveData();

    void ShopRun();
    void runMenu();

    void SnakeColorBuy(int a);
    //void runMenu();
};


#endif //FIRSTPROG_SHOP_H
