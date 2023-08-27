#include "Shop.h"
#include "MainMenu.h"
#include "iostream"

int Shop_currency;

Shop::Shop() {
    try {
        if (!font.loadFromFile("assets/fonts/slant_regular.ttf")) {
            throw "font not loaded!!!";
        }
    }
    catch (const char *txtE) {
        std::cout << "Exception: " << txtE << endl;
    }

    const Color &fillColor = sf::Color(255, 204, 153);
    Color altTextColor[] {
            sf::Color::Green,
            sf::Color::Red,
            sf::Color::Blue,
            sf::Color::Yellow
    };

    int mainTextFontSize = 35;
    int textChildFontSize = 20;

    String mainTextOptions[4]{"Green Snake", "Red Snake", "Blue Snake", "Yellow Snake"};
    String textChildCost = "Cost: 25 apples";
    String altTextOption = "Equipped";

    for (int i = 0; i < SHOP_ELEMENTS; ++i) {
        mainText[i] = sf::Text(mainTextOptions[i], font, mainTextFontSize);
        mainText[i].setFillColor(fillColor);
        mainText[i].setPosition(75, 110 + (120 * i));

        textChild[i] = sf::Text(textChildCost, font, textChildFontSize);
        textChild[i].setFillColor(fillColor);
        textChild[i].setPosition(75, 110 + (120 * i) + 40);

        altText[i] = sf::Text(altTextOption, font, textChildFontSize);
        altText[i].setFillColor(altTextColor[i]);
        altText[i].setPosition(75, 150 + (120 * i));
    }

    extraText[0].setFont(font);
    extraText[0].setFillColor(fillColor);
    extraText[0].setString("Press Q to quit to Main menu");
    extraText[0].setCharacterSize(30);
    extraText[0].setPosition(sf::Vector2f(420, 560));

    extraText[1].setFont(font);
    extraText[1].setFillColor(fillColor);
    extraText[1].setString("Apples: " + to_string(::Shop_currency));
    extraText[1].setCharacterSize(40);
    extraText[1].setPosition(sf::Vector2f(75, 25));

    ShopSelect = 0;
    mainText[ShopSelect].setFillColor(sf::Color::White);
}

void Shop::shopRun(sf::RenderWindow &window) {
    loadData();
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");
    sf::Texture background;
    background.loadFromFile("assets/texture/ShopMenu.png");
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
                if (event.key.code == Keyboard::Q) {
                    window.close();
//                    runMenu();
                }
                if (event.key.code == sf::Keyboard::Return) {
                    switch (ShopSelect) {
                        case 0:
                            if (returnBought(0) == 1) {
                                snakeColorBuy(0);
                            } else if (::Shop_currency >= 25) {
                                ::Shop_currency -= 25;
                                //cout << ::Shop_currency;
                                snakeColorBuy(0);
                                saveBought(1, 0, 0, 0);
                                saveData();
                            }
                            break;
                        case 1:
                            if (returnBought(1) == 1) {
                                snakeColorBuy(1);
                            } else if (::Shop_currency >= 25) {
                                ::Shop_currency -= 25;
                                snakeColorBuy(1);
                                saveBought(0, 1, 0, 0);
                                saveData();
                            }
                            break;
                        case 2:
                            if (returnBought(2) == 1) {
                                snakeColorBuy(2);
                            } else if (::Shop_currency >= 25) {
                                ::Shop_currency -= 25;
                                snakeColorBuy(2);
                                saveBought(0, 0, 1, 0);
                                saveData();
                            }
                            break;
                        case 3:
                            if (returnBought(3) == 1) {
                                snakeColorBuy(3);
                            } else if (::Shop_currency >= 50) {
                                ::Shop_currency -= 50;
                                snakeColorBuy(3);
                                saveBought(0, 0, 0, 1);
                                saveData();
                            }
                            break;
                    }
                }
            }
        }
        window.clear();
        window.draw(bg_image);
        drawExtra(window);
        draw(window);
        window.display();
    }
}

void Shop::moveUp() {
    if (ShopSelect == 0) {
        mainText[ShopSelect].setFillColor(sf::Color(255, 204, 153));
        ShopSelect = SHOP_ELEMENTS - 1;
        mainText[ShopSelect].setFillColor(sf::Color::White);
    } else {
        mainText[ShopSelect].setFillColor(sf::Color(255, 204, 153));
        ShopSelect--;
        mainText[ShopSelect].setFillColor(sf::Color::White);
    }
}

void Shop::moveDown() {
    if (ShopSelect == SHOP_ELEMENTS - 1) {
        mainText[ShopSelect].setFillColor(sf::Color(255, 204, 153));
        ShopSelect = 0;
        mainText[ShopSelect].setFillColor(sf::Color::White);
    } else {
        mainText[ShopSelect].setFillColor(sf::Color(255, 204, 153));
        ShopSelect++;
        mainText[ShopSelect].setFillColor(sf::Color::White);
    }
}

void Shop::draw(sf::RenderWindow &window) {
    int number;
    for (int c = 0; c <= 3; c++) {
        window.draw(mainText[c]);
        number = returnBought(c);
        if (number == 0) {
            window.draw(textChild[c]);
        } else {
            window.draw(altText[c]);
        }
    }

    /*
    for(const auto & i : mainText){
        window.draw(i);
    }
     */
}

void Shop::drawExtra(sf::RenderWindow &window) {
    extraText[1].setString("Apples: " + to_string(::Shop_currency));
    window.draw(extraText[0]);
    window.draw(extraText[1]);
}

void Shop::saveData() {
    //load previous data
    ifstream saveFileProfile("assets/save/dataProfile.txt");
    int apples;
    int score;
    if (saveFileProfile.is_open()) {
        saveFileProfile >> apples >> score;
        saveFileProfile.close();
    }

    //store new + old data
    ofstream saveProfile("assets/save/dataProfile.txt", ofstream::trunc);
    if (saveProfile.is_open()) {
        saveProfile << ::Shop_currency << endl << score;
        saveFileProfile.close();
    }
}

void Shop::loadData() {
    ifstream saveFileProfile("assets/save/dataProfile.txt");
    if (saveFileProfile.is_open()) {
        int a;
        saveFileProfile >> a;
        saveFileProfile.close();
        ::Shop_currency = a;
    }
}

int Shop::returnBought(int number) {
    //load previous data
    int GreenSnake, RedSnake, BlueSnake, YellowSnake;
    ifstream saveFileProfile("assets/save/Bought.txt");
    if (saveFileProfile.is_open()) {
        saveFileProfile >> GreenSnake >> RedSnake >> BlueSnake >> YellowSnake;
        saveFileProfile.close();
    }
    if (number == 0) {
        return GreenSnake;
    }
    if (number == 1) {
        return RedSnake;
    }
    if (number == 2) {
        return BlueSnake;
    }
    if (number == 3) {
        return YellowSnake;
    }
    return 0;
}

void Shop::saveBought(int a, int b, int c, int d) {
    int GreenSnake = 0;
    int RedSnake = 0;
    int BlueSnake = 0;
    int YellowSnake = 0;

    //load previous data
    ifstream saveFileProfile("assets/save/Bought.txt");
    if (saveFileProfile.is_open()) {
        saveFileProfile >> GreenSnake >> RedSnake >> BlueSnake >> YellowSnake;
        saveFileProfile.close();
    }

    //store new + old data
    ofstream saveProfile("assets/save/Bought.txt", ofstream::trunc);
    if (saveProfile.is_open()) {
        if(GreenSnake>=a){
            saveProfile<<GreenSnake<<endl;
        }
        else{
            saveProfile<<a<<endl;
        }
        if(RedSnake>=b){
            saveProfile<<RedSnake<<endl;
        }
        else{
            saveProfile<<b<<endl;
        }
        if(a!=BlueSnake){
            saveProfile<<BlueSnake<<endl;
        }
        else{
            saveProfile<<c<<endl;
        }
        if(a!=YellowSnake){
            saveProfile<<YellowSnake<<endl;
        }
        else{
            saveProfile<<d<<endl;
        }
        saveProfile.close();
    }
}

//void Shop::runMenu() {
//    MainMenu menu;
////    menu.menu();
//}

void Shop::snakeColorBuy(int a) {
    Snake::snakeColor(a);

}
