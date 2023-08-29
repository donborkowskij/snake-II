#include "Achievements.h"
#include <iostream>

Achievements::Achievements(std::shared_ptr<Param> param) : mParam(param) {
    if (!mFont.loadFromFile("assets/fonts/slant_regular.ttf")) {
        std::cerr << "mFont not loaded!!!";
        std::exit(EXIT_FAILURE);
    }

    loadData();

    TextInfo achieveTextInfo[] = {
            {"Apple I",         35, sf::Vector2f(75, 110), mGrayColor},
            {"Apple II",        35, sf::Vector2f(75, 220), mGrayColor},
            {"Apple III",       35, sf::Vector2f(75, 330), mGrayColor},
            {"Apple IV",        35, sf::Vector2f(75, 440), mGrayColor},
            {"Apple V",         35, sf::Vector2f(75, 110), mGrayColor},
            {"Apple VI",        35, sf::Vector2f(75, 220), mGrayColor},
            {"Apple VII",       35, sf::Vector2f(75, 330), mGrayColor},
            {"Score I",         35, sf::Vector2f(75, 440), mGrayColor},
            {"Score II",        35, sf::Vector2f(75, 110), mGrayColor},
            {"Score III",       35, sf::Vector2f(75, 220), mGrayColor},
            {"Score IV",        35, sf::Vector2f(75, 330), mGrayColor},
            {"Score V",         35, sf::Vector2f(75, 440), mGrayColor},
            {"Score VI",        35, sf::Vector2f(75, 110), mGrayColor},
            {"Score VII",       35, sf::Vector2f(75, 220), mGrayColor},
            {"Grand Secret I",  35, sf::Vector2f(75, 330), mGrayColor},
            {"Grand Secret II", 35, sf::Vector2f(75, 440), mGrayColor},
    };

    TextInfo textChildInfo[] = {
            {"You ate 1 Apple.",                   20, sf::Vector2f(75, 160), mGrayColor},
            {"You ate 10 apples.",                 20, sf::Vector2f(75, 270), mGrayColor},
            {"You ate 50 apples.",                 20, sf::Vector2f(75, 380), mGrayColor},
            {"You ate 100 apples.",                20, sf::Vector2f(75, 490), mGrayColor},
            {"You ate 200 apples.",                20, sf::Vector2f(75, 160), mGrayColor},
            {"You ate 500 apples.",                20, sf::Vector2f(75, 270), mGrayColor},
            {"You ate 1000 apples.",               20, sf::Vector2f(75, 380), mGrayColor},
            {"You got a score of 100 points.",     20, sf::Vector2f(75, 490), mGrayColor},
            {"You got a score of 1000 points.",    20, sf::Vector2f(75, 160), mGrayColor},
            {"You got a score of 5000 points.",    20, sf::Vector2f(75, 270), mGrayColor},
            {"You got a score of 10000 points.",   20, sf::Vector2f(75, 380), mGrayColor},
            {"You got a score of 50000 points.",   20, sf::Vector2f(75, 490), mGrayColor},
            {"You got a score of 1000000 points.", 20, sf::Vector2f(75, 160), mGrayColor},
            {"You got a score of 5000000 points.", 20, sf::Vector2f(75, 270), mGrayColor},
            {"A good n00b?",                       20, sf::Vector2f(75, 380), mGrayColor},
            {"2 funny numbers.",                   20, sf::Vector2f(75, 490), mGrayColor},
    };

    TextInfo extraTextInfo[] = {
            {"Press Q to quit to Main menu",                       30, sf::Vector2f(420, 560), mOrangeColor},
            {"Most apples eaten: " + std::to_string(mTotalApples), 40, sf::Vector2f(75, 5),    mOrangeColor},
            {"Your highest score: " + std::to_string(mMyScore),    40, sf::Vector2f(75, 45),   mOrangeColor},
    };

    for (int i = 0; i < ACHIEVEMENT_ELEMENTS; ++i) {
        mAchiveText[i].setFont(mFont);
        mAchiveText[i].setFillColor(achieveTextInfo[i].fillColor);
        mAchiveText[i].setString(achieveTextInfo[i].string);
        mAchiveText[i].setCharacterSize(achieveTextInfo[i].characterSize);
        mAchiveText[i].setPosition(achieveTextInfo[i].position);

        mTextChild[i].setFont(mFont);
        mTextChild[i].setFillColor(textChildInfo[i].fillColor);
        mTextChild[i].setString(textChildInfo[i].string);
        mTextChild[i].setCharacterSize(textChildInfo[i].characterSize);
        mTextChild[i].setPosition(textChildInfo[i].position);

        if (i < 3) {
            mExtraText[i].setFont(mFont);
            mExtraText[i].setFillColor(extraTextInfo[i].fillColor);
            mExtraText[i].setString(extraTextInfo[i].string);
            mExtraText[i].setCharacterSize(extraTextInfo[i].characterSize);
            mExtraText[i].setPosition(extraTextInfo[i].position);
        }
    }

    mBackground.loadFromFile("assets/texture/AchievementsMenu.png");
    mBgImage.setTexture(mBackground);
}

void Achievements::update(const sf::Time &deltaTime) {
    brain();
}

void Achievements::draw() {
    mParam->window->clear();
    mParam->window->draw(mBgImage);
    screen(mParam->window, mShopSelect);
    mParam->window->display();
}

void Achievements::input() {
    sf::Event event;
    while (mParam->window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                mParam->window->close();
                break;
            case sf::Event::KeyReleased:
                handleKeyInput(event.key.code);
                break;
            default:
                break;
        }
    }
}

void Achievements::handleKeyInput(sf::Keyboard::Key keyCode) {
    if (keyCode == sf::Keyboard::Down && mShopSelect != 12) {
        mShopSelect += 4;
    } else if (keyCode == sf::Keyboard::Up && mShopSelect != 0) {
        mShopSelect -= 4;
    } else if (keyCode == sf::Keyboard::Q) {
        mParam->states->add(std::make_unique<MainMenu>(mParam));
    }
}

void Achievements::screen(std::unique_ptr<sf::RenderWindow> &window, int i) {
    for (int j = 0; j < 4; ++j) {
        window->draw(mAchiveText[i + j]);
        window->draw(mTextChild[i + j]);
    }

    for (const auto &j: mExtraText) {
        window->draw(j);
    }
}

void Achievements::color(int i) {
    mAchiveText[i].setFillColor(sf::Color(212, 175, 55));
    mTextChild[i].setFillColor(sf::Color(212, 175, 55));
}

void Achievements::brain() {
    // Define the achievement conditions and colors
    std::pair<int, int> conditions[] = {
            {1,    0},
            {10,   1},
            {50,   2},
            {100,  3},
            {200,  4},
            {500,  5},
            {1000, 6}
    };

    std::pair<int, int> scoreConditions[] = {
            {100,    7},
            {1000,   8},
            {5000,   9},
            {10000,  10},
            {50000,  11},
            {100000, 12},
            {500000, 13}
    };

    for (auto const &i: conditions) {
        if (mTotalApples >= i.first)
            color(i.second);
    }

    for (auto const &i: scoreConditions) {
        if (mMyScore >= i.first)
            color(i.second);
    }

    // Additional special conditions
    if (mTotalApples == 1337) {
        color(14);
    }

    if (mTotalApples >= 69 && mMyScore >= 420) {
        color(15);
    }
}

void Achievements::loadData() {
    std::ifstream saveFileProfile("assets/save/dataProfile.txt");

    if (saveFileProfile.is_open()) {
        std::cout << "ACHIVE function" << std::endl;
        saveFileProfile >> mTotalApples >> mMyApples >> mMyScore;
        saveFileProfile.close();
        std::cout << "mTotalApples: " << mTotalApples << " mMyApples: " << mMyApples << " mMyScore: " << mMyScore
                  << std::endl;
    }
}
