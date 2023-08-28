#include "Shop.h"
#include "MainMenu.h"
#include "iostream"

int Shop_currency;

Shop::Shop(std::shared_ptr<Param> param) : mParam(param) {
    try {
        if (!mFont.loadFromFile("assets/fonts/slant_regular.ttf")) {
            throw "mFont not loaded!!!";
        }
    }
    catch (const char *txtE) {
        std::cout << "Exception: " << txtE << std::endl;
    }

    sf::Color altTextColor[]{
            sf::Color::Green,
            sf::Color::Red,
            sf::Color::Blue,
            sf::Color::Yellow
    };

    sf::String mainTextOptions[4]{"Green Snake", "Red Snake", "Blue Snake", "Yellow Snake"};
    sf::String textChildCost = "Cost: 25 apples";
    sf::String altTextOption = "Equipped";

    for (int i = 0; i < SHOP_ELEMENTS; ++i) {
        mMainText[i] = sf::Text(mainTextOptions[i], mFont, mMainTextFontSize);
        mMainText[i].setFillColor(mFillColor);
        mMainText[i].setPosition(75, 110 + (120 * i));

        mTextChild[i] = sf::Text(textChildCost, mFont, mTextChildFontSize);
        mTextChild[i].setFillColor(mFillColor);
        mTextChild[i].setPosition(75, 110 + (120 * i) + 40);

        mAltText[i] = sf::Text(altTextOption, mFont, mTextChildFontSize);
        mAltText[i].setFillColor(altTextColor[i]);
        mAltText[i].setPosition(75, 150 + (120 * i));
    }

    mExtraText[0].setFont(mFont);
    mExtraText[0].setFillColor(mFillColor);
    mExtraText[0].setString("Press Q to quit to Main menu");
    mExtraText[0].setCharacterSize(30);
    mExtraText[0].setPosition(sf::Vector2f(420, 560));

    mExtraText[1].setFont(mFont);
    mExtraText[1].setFillColor(mFillColor);
    mExtraText[1].setString("Apples: " + std::to_string(::Shop_currency));
    mExtraText[1].setCharacterSize(40);
    mExtraText[1].setPosition(sf::Vector2f(75, 25));

    mShopSelect = 0;
    mMainText[mShopSelect].setFillColor(sf::Color::White);

    mBackground.loadFromFile("assets/texture/ShopMenu.png");
    mBgImage.setTexture(mBackground);
}

void Shop::update(const sf::Time &deltaTime) {
    mMainText[mShopSelect].setCharacterSize(40);
    mMainText[mShopSelect].setFillColor(sf::Color::White);
}

void Shop::draw() {
    mParam->window->clear();
    mParam->window->draw(mBgImage);
    drawExtra(mParam->window);
    print(mParam->window);
    mParam->window->display();
}

void Shop::input() {
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
            if (event.key.code == sf::Keyboard::Q) {
                mParam->states->add(std::make_unique<MainMenu>(mParam), true);
            }
            if (event.key.code == sf::Keyboard::Return) {
                switch (mShopSelect) {
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
}

void Shop::moveUp() {
    if (mShopSelect == 0) {
        mMainText[mShopSelect].setFillColor(mFillColor);
        mMainText[mShopSelect].setCharacterSize(mMainTextFontSize);
        mShopSelect = SHOP_ELEMENTS - 1;
    } else {
        mMainText[mShopSelect].setFillColor(mFillColor);
        mMainText[mShopSelect].setCharacterSize(mMainTextFontSize);
        mShopSelect--;
    }
}

void Shop::moveDown() {
    if (mShopSelect == SHOP_ELEMENTS - 1) {
        mMainText[mShopSelect].setFillColor(mFillColor);
        mMainText[mShopSelect].setCharacterSize(mMainTextFontSize);
        mShopSelect = 0;
    } else {
        mMainText[mShopSelect].setFillColor(mFillColor);
        mMainText[mShopSelect].setCharacterSize(mMainTextFontSize);
        mShopSelect++;
    }
}

void Shop::print(std::unique_ptr<sf::RenderWindow> &window) {
    int number;
    for (int c = 0; c <= 3; c++) {
        window->draw(mMainText[c]);
        number = returnBought(c);
        if (number == 0) {
            window->draw(mTextChild[c]);
        } else {
            window->draw(mAltText[c]);
        }
    }
}

void Shop::drawExtra(std::unique_ptr<sf::RenderWindow> &window) {
    mExtraText[1].setString("Apples: " + std::to_string(::Shop_currency));
    window->draw(mExtraText[0]);
    window->draw(mExtraText[1]);
}

void Shop::saveData() {
    //load previous data
    std::ifstream saveFileProfile("assets/save/dataProfile.txt");
    int apples;
    int score;
    if (saveFileProfile.is_open()) {
        saveFileProfile >> apples >> score;
        saveFileProfile.close();
    }

    //store new + old data
    std::ofstream saveProfile("assets/save/dataProfile.txt", std::ofstream::trunc);
    if (saveProfile.is_open()) {
        saveProfile << ::Shop_currency << std::endl << score;
        saveFileProfile.close();
    }
}

void Shop::loadData() {
    std::ifstream saveFileProfile("assets/save/dataProfile.txt");
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
    std::ifstream saveFileProfile("assets/save/Bought.txt");
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
    std::ifstream saveFileProfile("assets/save/Bought.txt");
    if (saveFileProfile.is_open()) {
        saveFileProfile >> GreenSnake >> RedSnake >> BlueSnake >> YellowSnake;
        saveFileProfile.close();
    }

    //store new + old data
    std::ofstream saveProfile("assets/save/Bought.txt", std::ofstream::trunc);
    if (saveProfile.is_open()) {
        if (GreenSnake >= a) {
            saveProfile << GreenSnake << std::endl;
        } else {
            saveProfile << a << std::endl;
        }
        if (RedSnake >= b) {
            saveProfile << RedSnake << std::endl;
        } else {
            saveProfile << b << std::endl;
        }
        if (a != BlueSnake) {
            saveProfile << BlueSnake << std::endl;
        } else {
            saveProfile << c << std::endl;
        }
        if (a != YellowSnake) {
            saveProfile << YellowSnake << std::endl;
        } else {
            saveProfile << d << std::endl;
        }
        saveProfile.close();
    }
}

void Shop::snakeColorBuy(int a) {
    Snake::snakeColor(a);

}
