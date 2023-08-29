#include "Engine.h"
#include "Shop.h"
#include "MainMenu.h"
#include "Achievements.h"
#include <iostream>


MainMenu::MainMenu(std::shared_ptr<Param> param) : mParam(param) {
    try {
        if (!mFont.loadFromFile("assets/fonts/slant_regular.ttf")) {
            throw "mFont not loaded!!!";
        }
    }
    catch (const char *txtE) {
        std::cout << "Exception: " << txtE << std::endl;
    }

    sf::String menuOptions[MENU_ELEMENTS]{"Play", "Store", "Achievements", "Quit"};
    float position = 100;

    //menu buttons
    for (int i = 0; i < MENU_ELEMENTS; ++i) {
        mMainMenu[i] = sf::Text(menuOptions[i], mFont, mFontSize);
        mMainMenu[i].setFillColor(mFillColor);
        mMainMenu[i].setPosition(position, position * (float) (i + 1));
    }

    mMainMenuSelect = 0;
    mMainMenu[mMainMenuSelect].setFillColor(sf::Color::White);

    mBackground.loadFromFile("assets/texture/TitleScreen.png");
    mBgImage.setTexture(mBackground);
}

void MainMenu::update(const sf::Time &deltaTime) {
    mMainMenu[mMainMenuSelect].setCharacterSize(80);
    mMainMenu[mMainMenuSelect].setFillColor(sf::Color::White);
}

void MainMenu::draw() {
    mParam->window->clear();
    mParam->window->draw(mBgImage);
    print(mParam->window);
    mParam->window->display();
}

void MainMenu::input() {
    sf::Event event{};
    while (mParam->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mParam->window->close();
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Down) {
                moveDown();
            }
            if (event.key.code == sf::Keyboard::Up) {
                moveUp();
            }
            if (event.key.code == sf::Keyboard::Return) {
                switch (mMainMenuSelect) {
                    case 0:
                        mParam->states->add(std::make_unique<Engine>(mParam));
                        break;
                    case 1:
                        mParam->states->add(std::make_unique<Shop>(mParam));
                        break;
                    case 2:
                        mParam->states->add(std::make_unique<Achievements>(mParam));
                        break;
                    case 3:
                        mParam->window->close();
                        break;
                }
            }
        }
    }
}

void MainMenu::moveUp() {
    if (mMainMenuSelect == 0) {
        mMainMenu[mMainMenuSelect].setFillColor(mFillColor);
        mMainMenu[mMainMenuSelect].setCharacterSize(mFontSize);
        mMainMenuSelect = MENU_ELEMENTS - 1;
    } else {
        mMainMenu[mMainMenuSelect].setFillColor(mFillColor);
        mMainMenu[mMainMenuSelect].setCharacterSize(mFontSize);
        mMainMenuSelect--;
    }
}

void MainMenu::moveDown() {
    if (mMainMenuSelect == MENU_ELEMENTS - 1) {
        mMainMenu[mMainMenuSelect].setFillColor(mFillColor);
        mMainMenu[mMainMenuSelect].setCharacterSize(mFontSize);
        mMainMenuSelect = 0;
    } else {
        mMainMenu[mMainMenuSelect].setFillColor(mFillColor);
        mMainMenu[mMainMenuSelect].setCharacterSize(mFontSize);
        mMainMenuSelect++;
    }
}

void MainMenu::print(std::unique_ptr<sf::RenderWindow> &window) {
    for (const auto &i: mMainMenu) {
        window->draw(i);
    }
}
