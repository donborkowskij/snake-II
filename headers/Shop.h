#pragma once

#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "Snake.h"
#include <fstream>

#define SHOP_ELEMENTS 4

class Shop {
public:
    Shop();
    void shopRun(sf::RenderWindow &window);
    void runMenu();

private:
    int ShopSelect;
    sf::Font font;
    sf::Text mainText[SHOP_ELEMENTS];
    sf::Text textChild[SHOP_ELEMENTS];
    sf::Text altText[SHOP_ELEMENTS];
    sf::Text extraText[2];
    void moveUp();
    void moveDown();
    void draw(sf::RenderWindow &window);
    void drawExtra(sf::RenderWindow &window);
    void loadData();
    void saveBought(int GreenSnake, int RedSnake, int BlueSnake, int YellowSnake);
    int returnBought(int number);
    void saveData();
    void snakeColorBuy(int a);
};
