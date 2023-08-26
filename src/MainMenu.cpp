#include "Engine.h"
#include "Shop.h"
#include "MainMenu.h"
#include "Achievements.h"
#include "iostream"


MainMenu::MainMenu(sf::RenderWindow& window) {

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

    for (int i = 0; i < MENU_ELEMENTS; ++i) {
        mainMenu[i] = sf::Text(menuOptions[i], font, fontSize);
        mainMenu[i].setFillColor(fillColor);
        mainMenu[i].setPosition(position, position * (float) (i + 1));
    }

    mainMenuSelect = 0;
    mainMenu[mainMenuSelect].setFillColor(sf::Color::White);

    menuRun(window);
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

void MainMenu::draw(sf::RenderWindow &window) {
    for (const auto &i: mainMenu) {
        window.draw(i);
    }
}

void MainMenu::menuRun(RenderWindow& window) {
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake2");
    sf::Texture background;
    background.loadFromFile("assets/texture/TitleScreen.png");
    sf::Sprite bg_image(background);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
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
                            window.close();
                            runSnake();
                            break;
                        case 1:
                            window.close();
                            runShop();
                            break;
                        case 2:
                            window.close();
                            runAchievements();
                            break;
                        case 3:
                            window.close();
                            break;
                    }
                }
            }
        }
        window.clear();
        window.draw(bg_image);
        draw(window);
        window.display();
    }
}

void MainMenu::runSnake() {
    Engine engine;
    engine.run();
}

void MainMenu::runShop() {
    Shop shop;
    shop.shopRun();
}

void MainMenu::runAchievements() {
    Achievements achievements;
    achievements.achievementsRun();
}
