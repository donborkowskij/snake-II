#pragma once

#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "State.h"

class Achievements : public State {
public:
    Achievements(std::shared_ptr<Param> param);

    void update(const sf::Time &deltaTime) override;

    void draw() override;

    void input() override;

    void color(int i);

    void screen(std::unique_ptr<sf::RenderWindow> &window, int i);

    void brain();

private:
    std::shared_ptr<Param> mParam;
    sf::Font mFont;
    int mShopSelect;
    //Change this if you add more elements.
    sf::Text mAchiveText[16];
    sf::Text mTextChild[16];
    sf::Text mExtraText[3];

    sf::Texture mBackground;
    sf::Sprite mBgImage;

    void dataHandling();
};
