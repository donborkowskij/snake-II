#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Engine.h"

#define MENU_ELEMENTS 4


class MainMenu : public State {
public:
    explicit MainMenu(std::shared_ptr<Param> param);

    void update(const sf::Time& deltaTime) override;
    void draw() override;
    void input() override;
//    ----------
//    void menuRun(RenderWindow &window);

private:
    std::shared_ptr<Param> mParam;
    sf::Sprite bgImage;
    sf::Texture background;

    int mainMenuSelect;

    sf::Font font;
    sf::Text mainMenu[MENU_ELEMENTS];

    void moveUp();
    void moveDown();
    void print(std::unique_ptr<sf::RenderWindow> &window);

    bool isPlaySelected;

//    static void runSnake();
//    static void runShop(sf::RenderWindow& window);
//    static void runAchievements();
};
