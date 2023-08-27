#include "Engine.h"
#include "Shop.h"
#include "MainMenu.h"

#include <utility>
#include "Achievements.h"
#include "iostream"


MainMenu::MainMenu(std::shared_ptr<Param> param) : mParam(param){
    try {
        if (!font.loadFromFile("assets/fonts/slant_regular.ttf")) {
            throw "font not loaded!!!";
        }
    }
    catch (const char *txtE) {
        std::cout << "Exception: " << txtE << endl;
    }

    const Color &fillColor = sf::Color(255, 204, 153);
    int fontSize = 50;
    String menuOptions[4]{"Play", "Store", "Achievements", "Quit"};
    float position = 100;

    //menu buttons
    for (int i = 0; i < MENU_ELEMENTS; ++i) {
        mainMenu[i] = sf::Text(menuOptions[i], font, fontSize);
        mainMenu[i].setFillColor(fillColor);
        mainMenu[i].setPosition(position, position * (float) (i + 1));
    }

    mainMenuSelect = 0;
    mainMenu[mainMenuSelect].setFillColor(sf::Color::White);

    background.loadFromFile("assets/texture/TitleScreen.png");
    bgImage.setTexture(background);
}

void MainMenu::update(const sf::Time& deltaTime) {
    isPlaySelected = true;
}

void MainMenu::draw() {

    mParam->window->clear();
    mParam->window->draw(bgImage);
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
                switch (mainMenuSelect) {
                    case 0:
                        mParam->window->close();
//                        runSnake();
                        break;
                    case 1:
                        mParam->window->close();
//                        runShop(window);
                        break;
                    case 2:
                        mParam->window->close();
//                        runAchievements();
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
    if (mainMenuSelect == 0) {
        mainMenu[mainMenuSelect].setFillColor(sf::Color(255, 204, 153));
        mainMenuSelect = MENU_ELEMENTS - 1;
        mainMenu[mainMenuSelect].setFillColor(sf::Color::White);
    } else {
        mainMenu[mainMenuSelect].setFillColor(sf::Color(255, 204, 153));
        mainMenuSelect--;
        mainMenu[mainMenuSelect].setFillColor(sf::Color::White);
    }
}

void MainMenu::moveDown() {
    if (mainMenuSelect == MENU_ELEMENTS - 1) {
        mainMenu[mainMenuSelect].setFillColor(sf::Color(255, 204, 153));
        mainMenuSelect = 0;
        mainMenu[mainMenuSelect].setFillColor(sf::Color::White);
    } else {
        mainMenu[mainMenuSelect].setFillColor(sf::Color(255, 204, 153));
        mainMenuSelect++;
        mainMenu[mainMenuSelect].setFillColor(sf::Color::White);
    }
}

void MainMenu::print(std::unique_ptr<sf::RenderWindow> &window) {
    for (const auto &i: mainMenu) {
        window->draw(i);
    }
}

//void MainMenu::menuRun(RenderWindow &window) {
////    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake2");
//
//    while (window.isOpen()) {
//        sf::Event event{};
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//            if (event.type == sf::Event::KeyReleased) {
//                if (event.key.code == sf::Keyboard::Down) {
//                    moveDown();
//                }
//                if (event.key.code == sf::Keyboard::Up) {
//                    moveUp();
//                }
//                if (event.key.code == sf::Keyboard::Return) {
//                    switch (mainMenuSelect) {
//                        case 0:
//                            window.close();
//                            runSnake();
//                            break;
//                        case 1:
//                            window.close();
//                            runShop(window);
//                            break;
//                        case 2:
//                            window.close();
//                            runAchievements();
//                            break;
//                        case 3:
//                            window.close();
//                            break;
//                    }
//                }
//            }
//        }
//        window.clear();
//        window.draw(bgImage);
//        draw(window);
//        window.display();
//    }
//}

//void MainMenu::runSnake() {
//    Engine engine;
//    engine.run();
//}
//
//void MainMenu::runShop(sf::RenderWindow &window) {
//    Shop shop;
//    shop.shopRun(window);
//}
//
//void MainMenu::runAchievements() {
//    Achievements achievements;
//    achievements.achievementsRun();
//}
