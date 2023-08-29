#pragma once

#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "State.h"

#define ACHIEVEMENT_ELEMENTS 16

class Achievements : public State {
public:
    Achievements(std::shared_ptr<Param> param);

    void update(const sf::Time &deltaTime) override;

    void draw() override;

    void input() override;

private:
    void loadData();

    void handleKeyInput(sf::Keyboard::Key keyCode);

    void color(int i);

    void screen(std::unique_ptr<sf::RenderWindow> &window, int i);

    void brain();

    std::shared_ptr<Param> mParam;
    sf::Font mFont;
    sf::Text mAchiveText[ACHIEVEMENT_ELEMENTS];
    sf::Text mTextChild[ACHIEVEMENT_ELEMENTS];
    sf::Text mExtraText[3];
    const sf::Color mGrayColor = sf::Color(96, 96, 96);
    const sf::Color mOrangeColor = sf::Color(255, 204, 153);

    sf::Texture mBackground;
    sf::Sprite mBgImage;

    int mMyApples;
    int mMyScore;
    int mTotalApples;
    int mShopSelect = 0;

    struct TextInfo {
        std::string string;
        int characterSize;
        sf::Vector2f position;
        sf::Color fillColor;
    };
};
