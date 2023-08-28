#include "Achievements.h"
#include "iostream"

int Myapples;
int Myscore;
int TotalApples;
int ShopSelect = 0;

Achievements::Achievements(std::shared_ptr<Param> param) : mParam(param) {
    try {
        if (!mFont.loadFromFile("assets/fonts/slant_regular.ttf")) {
            throw "mFont not loaded!!!";
        }
    }
    catch (const char *txtE) {
        std::cout << "Exception: " << txtE << std::endl;
    }

    mAchiveText[0].setFont(mFont);
    mAchiveText[0].setFillColor(sf::Color(96, 96, 96));
    mAchiveText[0].setString("Apple I");
    mAchiveText[0].setCharacterSize(35);
    mAchiveText[0].setPosition(sf::Vector2f(75, 110));

    mAchiveText[1].setFont(mFont);
    mAchiveText[1].setFillColor(sf::Color(96, 96, 96));
    mAchiveText[1].setString("Apple II");
    mAchiveText[1].setCharacterSize(35);
    mAchiveText[1].setPosition(sf::Vector2f(75, 220));

    mAchiveText[2].setFont(mFont);
    mAchiveText[2].setFillColor(sf::Color(96, 96, 96));
    mAchiveText[2].setString("Apple III");
    mAchiveText[2].setCharacterSize(35);
    mAchiveText[2].setPosition(sf::Vector2f(75, 330));

    mAchiveText[3].setFont(mFont);
    mAchiveText[3].setFillColor(sf::Color(96, 96, 96));
    mAchiveText[3].setString("Apple IV");
    mAchiveText[3].setCharacterSize(35);
    mAchiveText[3].setPosition(sf::Vector2f(75, 440));

    mAchiveText[4].setFont(mFont);
    mAchiveText[4].setFillColor(sf::Color(96, 96, 96));
    mAchiveText[4].setString("Apple V");
    mAchiveText[4].setCharacterSize(35);
    mAchiveText[4].setPosition(sf::Vector2f(75, 110));

    mAchiveText[5].setFont(mFont);
    mAchiveText[5].setFillColor(sf::Color(96, 96, 96));
    mAchiveText[5].setString("Apple VI");
    mAchiveText[5].setCharacterSize(35);
    mAchiveText[5].setPosition(sf::Vector2f(75, 220));

    mAchiveText[6].setFont(mFont);
    mAchiveText[6].setFillColor(sf::Color(96, 96, 96));
    mAchiveText[6].setString("Apple VII");
    mAchiveText[6].setCharacterSize(35);
    mAchiveText[6].setPosition(sf::Vector2f(75, 330));


    mAchiveText[7].setFont(mFont);
    mAchiveText[7].setFillColor(sf::Color(96, 96, 96));
    mAchiveText[7].setString("Score I");
    mAchiveText[7].setCharacterSize(35);
    mAchiveText[7].setPosition(sf::Vector2f(75, 440));

    mAchiveText[8].setFont(mFont);
    mAchiveText[8].setFillColor(sf::Color(96, 96, 96));
    mAchiveText[8].setString("Score II");
    mAchiveText[8].setCharacterSize(35);
    mAchiveText[8].setPosition(sf::Vector2f(75, 110));

    mAchiveText[9].setFont(mFont);
    mAchiveText[9].setFillColor(sf::Color(96, 96, 96));
    mAchiveText[9].setString("Score III");
    mAchiveText[9].setCharacterSize(35);
    mAchiveText[9].setPosition(sf::Vector2f(75, 220));

    mAchiveText[10].setFont(mFont);
    mAchiveText[10].setFillColor(sf::Color(96, 96, 96));
    mAchiveText[10].setString("Score IV");
    mAchiveText[10].setCharacterSize(35);
    mAchiveText[10].setPosition(sf::Vector2f(75, 330));

    mAchiveText[11].setFont(mFont);
    mAchiveText[11].setFillColor(sf::Color(96, 96, 96));
    mAchiveText[11].setString("Score V");
    mAchiveText[11].setCharacterSize(35);
    mAchiveText[11].setPosition(sf::Vector2f(75, 440));

    mAchiveText[12].setFont(mFont);
    mAchiveText[12].setFillColor(sf::Color(96, 96, 96));
    mAchiveText[12].setString("Score VI");
    mAchiveText[12].setCharacterSize(35);
    mAchiveText[12].setPosition(sf::Vector2f(75, 110));

    mAchiveText[13].setFont(mFont);
    mAchiveText[13].setFillColor(sf::Color(96, 96, 96));
    mAchiveText[13].setString("Score VII");
    mAchiveText[13].setCharacterSize(35);
    mAchiveText[13].setPosition(sf::Vector2f(75, 220));

    mAchiveText[14].setFont(mFont);
    mAchiveText[14].setFillColor(sf::Color(96, 96, 96));
    mAchiveText[14].setString("Grand Secret I");
    mAchiveText[14].setCharacterSize(35);
    mAchiveText[14].setPosition(sf::Vector2f(75, 330));

    mAchiveText[15].setFont(mFont);
    mAchiveText[15].setFillColor(sf::Color(96, 96, 96));
    mAchiveText[15].setString("Grand Secret II");
    mAchiveText[15].setCharacterSize(35);
    mAchiveText[15].setPosition(sf::Vector2f(75, 440));


    mTextChild[0].setFont(mFont);
    mTextChild[0].setFillColor(sf::Color(96, 96, 96));
    mTextChild[0].setString("You ate 1 Apple.");
    mTextChild[0].setCharacterSize(20);
    mTextChild[0].setPosition(sf::Vector2f(75, 160));

    mTextChild[1].setFont(mFont);
    mTextChild[1].setFillColor(sf::Color(96, 96, 96));
    mTextChild[1].setString("You ate 10 apples.");
    mTextChild[1].setCharacterSize(20);
    mTextChild[1].setPosition(sf::Vector2f(75, 270));

    mTextChild[2].setFont(mFont);
    mTextChild[2].setFillColor(sf::Color(96, 96, 96));
    mTextChild[2].setString("You ate 50 apples.");
    mTextChild[2].setCharacterSize(20);
    mTextChild[2].setPosition(sf::Vector2f(75, 380));

    mTextChild[3].setFont(mFont);
    mTextChild[3].setFillColor(sf::Color(96, 96, 96));
    mTextChild[3].setString("You ate 100 apples.");
    mTextChild[3].setCharacterSize(20);
    mTextChild[3].setPosition(sf::Vector2f(75, 490));

    mTextChild[4].setFont(mFont);
    mTextChild[4].setFillColor(sf::Color(96, 96, 96));
    mTextChild[4].setString("You ate 200 Apple.");
    mTextChild[4].setCharacterSize(20);
    mTextChild[4].setPosition(sf::Vector2f(75, 160));

    mTextChild[5].setFont(mFont);
    mTextChild[5].setFillColor(sf::Color(96, 96, 96));
    mTextChild[5].setString("You ate 500 apples.");
    mTextChild[5].setCharacterSize(20);
    mTextChild[5].setPosition(sf::Vector2f(75, 270));

    mTextChild[6].setFont(mFont);
    mTextChild[6].setFillColor(sf::Color(96, 96, 96));
    mTextChild[6].setString("You ate 1000 apples.");
    mTextChild[6].setCharacterSize(20);
    mTextChild[6].setPosition(sf::Vector2f(75, 380));


    mTextChild[7].setFont(mFont);
    mTextChild[7].setFillColor(sf::Color(96, 96, 96));
    mTextChild[7].setString("You got a score of 100 points.");
    mTextChild[7].setCharacterSize(20);
    mTextChild[7].setPosition(sf::Vector2f(75, 490));

    mTextChild[8].setFont(mFont);
    mTextChild[8].setFillColor(sf::Color(96, 96, 96));
    mTextChild[8].setString("You got a score of 1000 points.");
    mTextChild[8].setCharacterSize(20);
    mTextChild[8].setPosition(sf::Vector2f(75, 160));

    mTextChild[9].setFont(mFont);
    mTextChild[9].setFillColor(sf::Color(96, 96, 96));
    mTextChild[9].setString("You got a score of 5000 points.");
    mTextChild[9].setCharacterSize(20);
    mTextChild[9].setPosition(sf::Vector2f(75, 270));

    mTextChild[10].setFont(mFont);
    mTextChild[10].setFillColor(sf::Color(96, 96, 96));
    mTextChild[10].setString("You got a score of 10000 points.");
    mTextChild[10].setCharacterSize(20);
    mTextChild[10].setPosition(sf::Vector2f(75, 380));

    mTextChild[11].setFont(mFont);
    mTextChild[11].setFillColor(sf::Color(96, 96, 96));
    mTextChild[11].setString("You got a score of 50000 points.");
    mTextChild[11].setCharacterSize(20);
    mTextChild[11].setPosition(sf::Vector2f(75, 490));

    mTextChild[12].setFont(mFont);
    mTextChild[12].setFillColor(sf::Color(96, 96, 96));
    mTextChild[12].setString("You got a score of 1000000 points.");
    mTextChild[12].setCharacterSize(20);
    mTextChild[12].setPosition(sf::Vector2f(75, 160));

    mTextChild[13].setFont(mFont);
    mTextChild[13].setFillColor(sf::Color(96, 96, 96));
    mTextChild[13].setString("You got a score of 500000 points.");
    mTextChild[13].setCharacterSize(20);
    mTextChild[13].setPosition(sf::Vector2f(75, 270));

    mTextChild[14].setFont(mFont);
    mTextChild[14].setFillColor(sf::Color(96, 96, 96));
    mTextChild[14].setString("A good n00b?");
    mTextChild[14].setCharacterSize(20);
    mTextChild[14].setPosition(sf::Vector2f(75, 380));

    mTextChild[15].setFont(mFont);
    mTextChild[15].setFillColor(sf::Color(96, 96, 96));
    mTextChild[15].setString("2 funny numbers.");
    mTextChild[15].setCharacterSize(20);
    mTextChild[15].setPosition(sf::Vector2f(75, 490));


    mExtraText[0].setFont(mFont);
    mExtraText[0].setFillColor(sf::Color(255, 204, 153));
    mExtraText[0].setString("Press Q to quit to Main menu");
    mExtraText[0].setCharacterSize(30);
    mExtraText[0].setPosition(sf::Vector2f(420, 560));

    mExtraText[1].setFont(mFont);
    mExtraText[1].setFillColor(sf::Color(255, 204, 153));
    mExtraText[1].setString("Most apples eaten: " + std::to_string(::Myapples));
    mExtraText[1].setCharacterSize(40);
    mExtraText[1].setPosition(sf::Vector2f(75, 5));

    mExtraText[2].setFont(mFont);
    mExtraText[2].setFillColor(sf::Color(255, 204, 153));
    mExtraText[2].setString("Your highest score: " + std::to_string(::Myscore));
    mExtraText[2].setCharacterSize(40);
    mExtraText[2].setPosition(sf::Vector2f(75, 45));


    mBackground.loadFromFile("assets/texture/AchievementsMenu.png");
    mBgImage.setTexture(mBackground);
}

void Achievements::update(const sf::Time &deltaTime) {
    brain();
}

void Achievements::draw() {
    mParam->window->clear();
    mParam->window->draw(mBgImage);
    screen(mParam->window, ::ShopSelect);
    mParam->window->display();
}

void Achievements::input() {
    sf::Event event{};
    while (mParam->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mParam->window->close();
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Down) {
                if (::ShopSelect != 12) {
                    ::ShopSelect += 4;
                }
            }
            if (event.key.code == sf::Keyboard::Up) {
                if (::ShopSelect != 0) {
                    ::ShopSelect -= 4;
                }
            }
            if (event.key.code == sf::Keyboard::Q) {
                mParam->window->close();
//                    runMenu();
            }

        }

    }
}

void Achievements::screen(std::unique_ptr<sf::RenderWindow> &window, int i) {
    window->draw(mAchiveText[i]);
    window->draw(mAchiveText[i + 1]);
    window->draw(mAchiveText[i + 2]);
    window->draw(mAchiveText[i + 3]);
    window->draw(mTextChild[i]);
    window->draw(mTextChild[i + 1]);
    window->draw(mTextChild[i + 2]);
    window->draw(mTextChild[i + 3]);
    window->draw(mExtraText[0]);
    window->draw(mExtraText[1]);
    window->draw(mExtraText[2]);
}

void Achievements::color(int i) {
    mAchiveText[i].setFillColor(sf::Color(212, 175, 55));
    mTextChild[i].setFillColor(sf::Color(212, 175, 55));
}

void Achievements::dataHandling() {
    //load previous data
    std::ifstream saveFileProfile("assets/save/dataProfile.txt");

    if (saveFileProfile.is_open()) {
        saveFileProfile >> ::Myapples >> ::Myscore >> ::TotalApples;
        saveFileProfile.close();
    }
    mExtraText[1].setString("Most apples eaten: " + std::to_string(::TotalApples));
    mExtraText[2].setString("Your highest score: " + std::to_string(::Myscore));
    //Why did i create this?
}


void Achievements::brain() {
    if (::TotalApples >= 1) {
        color(0);
    }
    if (::TotalApples >= 10) {
        color(1);
    }
    if (::TotalApples >= 50) {
        color(2);
    }
    if (::TotalApples >= 100) {
        color(3);
    }
    if (::TotalApples >= 200) {
        color(4);
    }
    if (::TotalApples >= 500) {
        color(5);
    }
    if (::TotalApples >= 1000) {
        color(6);
    }
    if (::Myscore >= 100) {
        color(7);
    }
    if (::Myscore >= 1000) {
        color(8);
    }
    if (::Myscore >= 5000) {
        color(9);
    }
    if (::Myscore >= 10000) {
        color(10);
    }
    if (::Myscore >= 50000) {
        color(11);
    }
    if (::Myscore >= 100000) {
        color(12);
    }
    if (::Myscore >= 500000) {
        color(13);
    }
    if (::TotalApples == 1337) {
        color(14);
    }
    if (::TotalApples >= 69 && ::Myscore >= 420) {
        color(15);
    }
}
