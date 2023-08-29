#include "Engine.h"
#include <iostream>

Engine::Engine(std::shared_ptr<Param> param) : mParam(param) {
    if (!mFont.loadFromFile("assets/fonts/slant_regular.ttf")) {
        std::cerr << "mFont not loaded!!!";
        std::exit(EXIT_FAILURE);
    }

    mResolution = sf::Vector2f(800, 600);
    mParam->window->setFramerateLimit(FPS);
    mMaxLevels = 0;
    checkLevelFiles();

    sf::FloatRect textBounds;

    // Title Text
    setupText(&mTitleText, mFont, "Snake II", 28, sf::Color::Blue);
    textBounds = mTitleText.getLocalBounds();
    mTitleText.setPosition(sf::Vector2f(mResolution.x / 2 - textBounds.width / 2, -9));

    // Current Level Text
    setupText(&mCurrentLevelText, mFont, "level 1", 28, sf::Color::Blue);
    mCurrentLevelText.setPosition(sf::Vector2f(15, -9));
    textBounds = mCurrentLevelText.getGlobalBounds();

    // Apples Eaten Text
    setupText(&mApplesEatenText, mFont, "apples 0", 28, sf::Color::Blue);
    mApplesEatenText.setPosition(sf::Vector2f(textBounds.left + textBounds.width + 20, -9));

    // Score Text
    setupText(&mScoreText, mFont, std::to_string(mScore), 28, sf::Color::Blue);
    textBounds = mScoreText.getLocalBounds();
    mScoreText.setPosition(mResolution.x - textBounds.width - 15, -9);

    // Game Over Text
    setupText(&mGameOverText, mFont, "GAME OVER", 72, sf::Color::Yellow);
    textBounds = mGameOverText.getLocalBounds();
    mGameOverText.setPosition(sf::Vector2f(mResolution.x / 2 - textBounds.width / 2, 100));
    mGameOverText.setOutlineColor(sf::Color::Black);
    mGameOverText.setOutlineThickness(2);

    // Quit to Menu Text
    setupText(&mQuitToMenuText, mFont, "Press Q to quit to Main menu", 30, sf::Color::Yellow);
    textBounds = mQuitToMenuText.getLocalBounds();
    mQuitToMenuText.setPosition(sf::Vector2f(mResolution.x / 2 - textBounds.width / 2, 500));
    mQuitToMenuText.setOutlineColor(sf::Color::Black);
    mQuitToMenuText.setOutlineThickness(1);

    // Press Space Text
    setupText(&mPressSpaceText, mFont, "Press SPACE to try again", 38, sf::Color::Green);
    textBounds = mPressSpaceText.getLocalBounds();
    mPressSpaceText.setPosition(sf::Vector2f(mResolution.x / 2 - textBounds.width / 2, 200));
    mPressSpaceText.setOutlineColor(sf::Color::Black);
    mPressSpaceText.setOutlineThickness(2);

    startTheGame();
}

void Engine::update(const sf::Time &deltaTime) {
    if (mCurrentGameState != GameState::PAUSED) {
        if (mCurrentGameState != GameState::GAMEOVER) {
            mTimeSinceLastMove += deltaTime;

            if (mTimeSinceLastMove.asSeconds() >= sf::seconds(1.f / float(mSpeed)).asSeconds()) {
                sf::Vector2f thisSectionPosition = mSnake[0].getPosition();
                sf::Vector2f lastSectionPosition = thisSectionPosition;

                handleDirectionChange();

                updateScore();

                updateSnake(thisSectionPosition, lastSectionPosition);

                collisionWithApple();

                collisionGameOver();

                mTimeSinceLastMove = sf::Time::Zero;
            }
        }
    }
}

void Engine::draw() {
    mParam->window->clear(sf::Color::Black);

    for (auto &w: mWallSections) {
        mParam->window->draw(w.getShape());
    }

    mParam->window->draw(mApple.getSprite());

    for (auto &s: mSnake) {
        mParam->window->draw(s.getShape());
    }

    mParam->window->draw(mTitleText);
    mParam->window->draw(mCurrentLevelText);
    mParam->window->draw(mApplesEatenText);
    mParam->window->draw(mScoreText);

    if (mCurrentGameState == GameState::GAMEOVER) {
        mParam->window->draw(mGameOverText);
        mParam->window->draw(mPressSpaceText);
        mParam->window->draw(mQuitToMenuText);
    }

    mParam->window->display();
}

void Engine::input() {
    sf::Event event{};

    while (mParam->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mParam->window->close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                mParam->window->close();
            }

            togglePause(event);

            if (mCurrentGameState == GameState::GAMEOVER) {
                if (event.key.code == sf::Keyboard::Space) {
                    saveData();
                    startTheGame();
                } else if (event.key.code == sf::Keyboard::Q) {
                    saveData();
                    mParam->states->add(std::make_unique<MainMenu>(mParam));
                }
            }

            switch (event.key.code) {
                case sf::Keyboard::Up:
                    addDirection(Direction::UP);
                    break;
                case sf::Keyboard::Down:
                    addDirection(Direction::DOWN);
                    break;
                case sf::Keyboard::Left:
                    addDirection(Direction::LEFT);
                    break;
                case sf::Keyboard::Right:
                    addDirection(Direction::RIGHT);
                    break;
                default:
                    break;
            }
        }
    }
}

void Engine::startTheGame() {
    // Reset game parameters
    mScore = 0;
    mSpeed = 5;
    mSnakeDirection = Direction::RIGHT;
    mTimeSinceLastMove = sf::Time::Zero;

    // Reset mSnake and level data
    mSectionsToAdd = 0;
    mDirectionQueue.clear();
    mWallSections.clear();
    mApplesEatenThisLevel = 0;
    mApplesEatenTotal = 0;
    mCurrentLevel = 1;
    loadLevel(mCurrentLevel);
    newSnake();
    moveApple();
    mCurrentGameState = GameState::RUNNING;
    mLastGameState = mCurrentGameState;

    // Update UI elements
    mCurrentLevelText.setString("level " + std::to_string(mCurrentLevel));
    mApplesEatenText.setString("apples " + std::to_string(mApplesEatenTotal));

    sf::FloatRect currentLevelTextBounds = mCurrentLevelText.getGlobalBounds();
    sf::FloatRect scoreTextBounds = mScoreText.getLocalBounds();

    // Update positions of UI elements
    mApplesEatenText.setPosition
            (sf::Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));
    mScoreText.setString(std::to_string(mScore));
    mScoreText.setPosition(mResolution.x - scoreTextBounds.width - 15, -9);
}

//load next level and reset the Snake
void Engine::beginNextLevel() {
    mCurrentLevel += 1;
    mWallSections.clear();
    mDirectionQueue.clear();
    mSpeed = 2 + mCurrentLevel;
    mSnakeDirection = Direction::RIGHT;
    mSectionsToAdd = 0;
    mApplesEatenThisLevel = 0;

    loadLevel(mCurrentLevel);
    newSnake();
    moveApple();
    mCurrentLevelText.setString("level " + std::to_string(mCurrentLevel));
    sf::FloatRect currentLevelTextBounds = mCurrentLevelText.getGlobalBounds();
    mApplesEatenText.setPosition
            (sf::Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));
}

//new Snake at the beginning of a level;
void Engine::newSnake() {
    mSnake.clear();
    mSnake.emplace_back(sf::Vector2f(100, 100));
    mSnake.emplace_back(sf::Vector2f(80, 100));
    mSnake.emplace_back(sf::Vector2f(60, 100));
}

//The tail of the Snake, to elongate the body
void Engine::addSnake() {
    sf::Vector2f newSectionPosition = mSnake[mSnake.size() - 1].getPosition();
    mSnake.emplace_back(newSectionPosition);
}

void Engine::moveApple() {
    //Find a location to place the Apple(not inside Snake/Wall)

    //Divide the field into sections the size of the Apple - except the walls
    sf::Vector2f appleResolution = sf::Vector2f(mResolution.x / 20 - 2, mResolution.y / 20 - 2);
    sf::Vector2f newAppleLocation;
    bool badLocation = false;
    srand(time(nullptr));
    //loop to find good locations
    do {
        badLocation = false;
        //generate random location
        newAppleLocation.x = (float) (1 + rand() / ((RAND_MAX + 1u) / (int) appleResolution.x)) * 20;
        newAppleLocation.y = (float) (1 + rand() / ((RAND_MAX + 1u) / (int) appleResolution.y)) * 20;

        //check if it's in the Snake
        for (auto &s: mSnake) {
            if (s.getShape().getGlobalBounds().intersects(
                    sf::Rect<float>(newAppleLocation.x, newAppleLocation.y, 20, 20))) {
                badLocation = true;
                break;
            }
        }

        //check if its in the Wall
        for (auto &w: mWallSections) {
            if (w.getShape().getGlobalBounds().intersects(
                    sf::Rect<float>(newAppleLocation.x, newAppleLocation.y, 20, 20))) {
                badLocation = true;
                break;
            }
        }

    } while (badLocation);
    mApple.setPosition(newAppleLocation);
}

void Engine::togglePause(sf::Event& event) {
    if (event.key.code == sf::Keyboard::Pause) {
        if (mCurrentGameState == GameState::RUNNING) {
            mLastGameState = mCurrentGameState;
            mCurrentGameState = GameState::PAUSED;
        } else if (mCurrentGameState == GameState::PAUSED) {
            mCurrentGameState = mLastGameState;
        }
    }
}

void Engine::setupText(sf::Text *textItem,const sf::Font &font,const sf::String &value,int size,sf::Color colour) {
    textItem->setFont(font);
    textItem->setString(value);
    textItem->setCharacterSize(size);
    textItem->setFillColor(colour);
}

void Engine::checkLevelFiles() {
    //Load the levels file
    std::ifstream levelsManifest("assets/levels/levels.txt");
    std::ifstream testFile;
    for (std::string manifestLine; getline(levelsManifest, manifestLine);) {
        //check that the level file opens
        testFile.open("assets/levels/" + manifestLine);
        if (testFile.is_open()) {
            //the file opens -> add to the list of levels
            levels.emplace_back("assets/levels/" + manifestLine);
            testFile.close();
            mMaxLevels++;
        }
    }
    levelsManifest.close();
}

//checks a level from a file and converts 'x' characters to add Wall
void Engine::loadLevel(int levelNumber) {
    std::string levelFile = levels.at(levelNumber - 1);
    std::ifstream level(levelFile);
    std::string line;
    if (level.is_open()) {
        for (int y = 0; y < 30; y++) {
            getline(level, line);
            for (int x = 0; x < 40; x++) {
                if (line[x] == 'x') {
                    mWallSections.emplace_back(Wall(sf::Vector2f(x * 20, y * 20), sf::Vector2f(20, 20)));
                }
            }
        }
        level.close();
    }
}

void Engine::saveData() const {
    std::ifstream loadFile("assets/save/dataProfile.txt");
    int TotalApples;
    int applesEaten;
    size_t highScore;
    if (loadFile.is_open()) {
        loadFile >> TotalApples >> applesEaten >> highScore;
        loadFile.close();
    }

    std::ofstream saveProfile("assets/save/dataProfile.txt");
    if (saveProfile.is_open()) {
        saveProfile << (applesEaten + mApplesEatenTotal) << std::endl;

        if (TotalApples < mApplesEatenTotal) {
            saveProfile << mApplesEatenTotal << std::endl;
        } else {
            saveProfile << TotalApples << std::endl;
        }

        if (highScore < mScore) {
            saveProfile << mScore << std::endl;
        } else {
            saveProfile << highScore;
        }
        saveProfile.close();
    }
}

void Engine::addDirection(int newDirection) {
    if (mDirectionQueue.empty() || mDirectionQueue.back() != newDirection) {
        mDirectionQueue.emplace_back(newDirection);
    }
}

void Engine::handleDirectionChange() {
    if (!mDirectionQueue.empty()) {
        auto newDirection = static_cast<Direction>(mDirectionQueue.front());
        switch (mSnakeDirection) {
            case Direction::UP:
                mSnakeDirection = (newDirection != Direction::DOWN) ? newDirection : mSnakeDirection;
                break;
            case Direction::DOWN:
                mSnakeDirection = (newDirection != Direction::UP) ? newDirection : mSnakeDirection;
                break;
            case Direction::LEFT:
                mSnakeDirection = (newDirection != Direction::RIGHT) ? newDirection : mSnakeDirection;
                break;
            case Direction::RIGHT:
                mSnakeDirection = (newDirection != Direction::LEFT) ? newDirection : mSnakeDirection;
                break;
        }
        mDirectionQueue.pop_front();
    }
}

void Engine::updateScore() {
    mScore += mSnake.size() + (mApplesEatenTotal + 1);
    mScoreText.setString(std::to_string(mScore));
    sf::FloatRect scoreTextBounds = mScoreText.getLocalBounds();
    mScoreText.setPosition(mResolution.x - scoreTextBounds.width - 15, -9);
}

void Engine::updateSnake(sf::Vector2f thisSectionPosition, sf::Vector2f lastSectionPosition) {
    if (mSectionsToAdd) {
        addSnake();
        mSectionsToAdd--;
    }

    //Update snakes head position
    switch (mSnakeDirection) {
        case Direction::RIGHT:
            mSnake[0].setPosition(sf::Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
            break;
        case Direction::DOWN:
            mSnake[0].setPosition(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
            break;
        case Direction::LEFT:
            mSnake[0].setPosition(sf::Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
            break;
        case Direction::UP:
            mSnake[0].setPosition(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
            break;
    }

    //Update mSnake tail position
    for (size_t s = 1; s < mSnake.size(); s++) {
        thisSectionPosition = mSnake[s].getPosition();
        mSnake[s].setPosition(lastSectionPosition);
        lastSectionPosition = thisSectionPosition;
    }

    for (auto &s: mSnake) {
        s.update();
    }
}

void Engine::collisionWithApple() {
    if (checkCollision(mSnake[0].getShape(), mApple.getSprite())) {
        mApplesEatenThisLevel += 1;
        mApplesEatenTotal += 1;
        mApplesEatenText.setString("apples " + std::to_string(mApplesEatenTotal));
        sf::FloatRect currentLevelTextBounds = mCurrentLevelText.getGlobalBounds();
        mApplesEatenText.setPosition(sf::Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));

        bool beginningNewLevel = false;
        if (mApplesEatenThisLevel >= 10) {
            if (mCurrentLevel < mMaxLevels) {
                beginningNewLevel = true;
                beginNextLevel();
            }
        }
        if (!beginningNewLevel) {
            mSectionsToAdd += 4;
            mSpeed++;
            moveApple();
        }
    }
}

void Engine::collisionGameOver() {
    for (size_t s = 1; s < mSnake.size(); s++) {
        if (checkCollision(mSnake[0].getShape(), mSnake[s].getShape())) {
            toggleGameOver();
        }
    }

    for (auto &w: mWallSections) {
        if (checkCollision(mSnake[0].getShape(), w.getShape())) {
            toggleGameOver();
        }
    }
}

bool Engine::checkCollision(sf::RectangleShape shape1, sf::RectangleShape shape2) {
    return shape1.getGlobalBounds().intersects(shape2.getGlobalBounds());
}

void Engine::toggleGameOver() {
    mCurrentGameState = GameState::GAMEOVER;
}
