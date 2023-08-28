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

    void update(const sf::Time &deltaTime) override;

    void draw() override;

    void input() override;

private:
    std::shared_ptr<Param> mParam;
    sf::Sprite mBgImage;
    sf::Texture mBackground;
    sf::Font mFont;
    sf::Text mMainMenu[MENU_ELEMENTS];
    const sf::Color mFillColor = sf::Color(255, 204, 153);
    int mMainMenuSelect;
    int mFontSize = 50;

    void moveUp();

    void moveDown();

    void print(std::unique_ptr<sf::RenderWindow> &window);
};
