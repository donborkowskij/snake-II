#include "Engine.h"
#include "Shop.h"
#include "MainMenu.h"
#include "Achievements.h"
#include "iostream"



void MainMenu::Menu() {


    if(!font.loadFromFile("assets/fonts/slant_regular.ttf")){
        //give some error message
    }

    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(sf::Color(255, 204, 153));
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(50);
    mainMenu[0].setPosition(sf::Vector2f(50, 50));

    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(sf::Color(255, 204, 153));
    mainMenu[1].setString("Store");
    mainMenu[1].setCharacterSize(50);
    mainMenu[1].setPosition(sf::Vector2f(50, 100));

    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(sf::Color(255, 204, 153));
    mainMenu[2].setString("Achievements");
    mainMenu[2].setCharacterSize(50);
    mainMenu[2].setPosition(sf::Vector2f(50, 150));

    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(sf::Color(255, 204, 153));
    mainMenu[3].setString("Quit");
    mainMenu[3].setCharacterSize(50);
    mainMenu[3].setPosition(sf::Vector2f(50, 200));

    mainMenuSelect = 0;
    mainMenu[mainMenuSelect].setFillColor(sf::Color::White);

    MenuRun();
}

void MainMenu::moveUp(){

    if(mainMenuSelect == 0){
        mainMenu[mainMenuSelect].setFillColor(sf::Color(255, 204, 153));

        //Change this if there are more menu options.
        mainMenuSelect = 3;

        mainMenu[mainMenuSelect].setFillColor(sf::Color::White);
    }
    else{
    mainMenu[mainMenuSelect].setFillColor(sf::Color(255, 204, 153));
    mainMenuSelect--;
    mainMenu[mainMenuSelect].setFillColor(sf::Color::White);
    }
}

void MainMenu::moveDown(){

    if(mainMenuSelect == 3){
        mainMenu[mainMenuSelect].setFillColor(sf::Color(255, 204, 153));

        //Change this if there are more menu options.
        mainMenuSelect = 0;

        mainMenu[mainMenuSelect].setFillColor(sf::Color::White);
    }
    else{
        mainMenu[mainMenuSelect].setFillColor(sf::Color(255, 204, 153));
        mainMenuSelect++;
        mainMenu[mainMenuSelect].setFillColor(sf::Color::White);
    }
}

void MainMenu::Draw(sf::RenderWindow &window) {
    for(const auto & i : mainMenu){
        window.draw(i);
    }
}

void MainMenu::MenuRun() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");
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
                            RunSnake();
                            break;
                        case 1:
                            window.close();
                            RunShop();
                            break;
                        case 2:
                            window.close();
                            RunAchievements();
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
        Draw(window);
        window.display();



    }
}
void MainMenu::RunSnake(){
    Engine engine;
    engine.run();
}
void MainMenu::RunShop(){
    Shop shop;
    shop.ShopRun();
}
void MainMenu::RunAchievements(){
    Achievements achievements;
    achievements.AchievementsRun();
}
//engine.run();