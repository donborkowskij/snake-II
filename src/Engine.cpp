#include "Engine.h"
#include "iostream"

const sf::Time Engine::TimePerFrame = sf::seconds(1.f / 60.f);

Engine::Engine(std::shared_ptr<Param> param) : mParam(param) {

    try {
        if (!mFont.loadFromFile("assets/fonts/slant_regular.ttf")) {
            throw "mFont not loaded!!!";
        }
    }
    catch (const char *txtE) {
        std::cout << "Exception: " << txtE << std::endl;
    }

    resolution = sf::Vector2f(800, 600);
    mParam->window->setFramerateLimit(FPS);
    maxLevels = 0;
    checkLevelFiles();

//    startTheGame();

    setupText(&titleText, mFont, "Snake", 28, sf::Color::Blue);
    sf::FloatRect titleTextBounds = titleText.getLocalBounds();
    titleText.setPosition(sf::Vector2f(resolution.x / 2 - titleTextBounds.width / 2, -9));

    setupText(&currentLevelText, mFont, "level 1", 28, sf::Color::Blue);
    currentLevelText.setPosition(sf::Vector2f(15, -9));
    sf::FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();

    setupText(&applesEatenText, mFont, "apples 0", 28, sf::Color::Blue);
    applesEatenText.setPosition(sf::Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));

    setupText(&scoreText, mFont, std::to_string(score), 28, sf::Color::Blue);
    sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setPosition(resolution.x - scoreTextBounds.width - 15, -9);

    setupText(&gameOverText, mFont, "GAME OVER", 72, sf::Color::Yellow);
    sf::FloatRect gameOverTextBounds = gameOverText.getLocalBounds();
    gameOverText.setPosition(sf::Vector2f(resolution.x / 2 - gameOverTextBounds.width / 2, 100));
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setOutlineThickness(2);

    setupText(&quitToMenuText, mFont, "Press Q to quit to Main menu", 30, sf::Color::Yellow);
    sf::FloatRect quitToMenuBounds = quitToMenuText.getLocalBounds();
    quitToMenuText.setPosition(sf::Vector2f(resolution.x / 2 - quitToMenuBounds.width / 2, 500));
    quitToMenuText.setOutlineColor(sf::Color::Black);
    quitToMenuText.setOutlineThickness(1);

    setupText(&pressSpaceText, mFont, "Press SPACE to try again", 38, sf::Color::Green);
    sf::FloatRect pressSpaceTextBounds = pressSpaceText.getLocalBounds();
    pressSpaceText.setPosition(sf::Vector2f(resolution.x / 2 - pressSpaceTextBounds.width / 2, 200));
    pressSpaceText.setOutlineColor(sf::Color::Black);
    pressSpaceText.setOutlineThickness(2);

//    dt = clock.restart();
    startTheGame();
}

void Engine::update(const sf::Time &deltaTime) {
    timeSinceLastMove += deltaTime;

    //Update snake position
    if (timeSinceLastMove.asSeconds() >= sf::seconds(1.f / float(speed)).asSeconds()) {
        sf::Vector2f thisSectionPosition = snake[0].getPosition();
        sf::Vector2f lastSectionPosition = thisSectionPosition;

        if (!directionQueue.empty()) {
            auto newDirection = static_cast<Direction>(directionQueue.front());
            //Make sure the snake doesn't go into apposite direction
            switch (snakeDirection) {
                case Direction::UP:
                    snakeDirection = (newDirection != Direction::DOWN) ? newDirection : snakeDirection;
                    break;
                case Direction::DOWN:
                    snakeDirection = (newDirection != Direction::UP) ? newDirection : snakeDirection;
                    break;
                case Direction::LEFT:
                    snakeDirection = (newDirection != Direction::RIGHT) ? newDirection : snakeDirection;
                    break;
                case Direction::RIGHT:
                    snakeDirection = (newDirection != Direction::LEFT) ? newDirection : snakeDirection;
                    break;
            }
            directionQueue.pop_front();
        }

        //Update Score
        score += snake.size() + (applesEatenTotal + 1);
        scoreText.setString(std::to_string(score));
        sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
        scoreText.setPosition(resolution.x - scoreTextBounds.width - 15, -9);

        //Do we need to grow the snake
        if (sectionsToAdd) {
            addSnake();
            sectionsToAdd--;
        }

        //Update snakes head position
        switch (snakeDirection) {
            case Direction::RIGHT:
                snake[0].setPosition(sf::Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
                break;
            case Direction::DOWN:
                snake[0].setPosition(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
                break;
            case Direction::LEFT:
                snake[0].setPosition(sf::Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
                break;
            case Direction::UP:
                snake[0].setPosition(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
                break;
        }

        //Update snake tail position
        for (int s = 1; s < snake.size(); s++) {
            thisSectionPosition = snake[s].getPosition();
            snake[s].setPosition(lastSectionPosition);
            lastSectionPosition = thisSectionPosition;
        }

        // update snake functions
        for (auto &s: snake) {
            s.update();
        }

        //Collision detection with Apple
        if (snake[0].getShape().getGlobalBounds().intersects(apple.getSprite().getGlobalBounds())) {
            applesEatenThisLevel += 1;
            applesEatenTotal += 1;
            applesEatenText.setString("apples " + std::to_string(applesEatenTotal));
            sf::FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
            applesEatenText.setPosition(
                    sf::Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));

            //see if need to load new level
            bool beginningNewLevel = false;
            if (applesEatenThisLevel >= 10) {
                //Begin the next level if there are more levels, else just play current level
                if (currentLevel < maxLevels) {
                    beginningNewLevel = true;
                    beginNextLevel();
                }
            }
            if (!beginningNewLevel) {
                //We hit the apple, increase speed/snake size
                sectionsToAdd += 4;
                speed++;
                moveApple();
            }
        }

        //collision with snake body
        for (int s = 1; s < snake.size(); s++) {
            if (snake[0].getShape().getGlobalBounds().intersects(snake[s].getShape().getGlobalBounds())) {
                //game over
                currentGameState = GameState::GAMEOVER;
            }
        }

        //Collision with wall
        for (auto &w: wallSections) {
            if (snake[0].getShape().getGlobalBounds().intersects(w.getShape().getGlobalBounds())) {
                //Game over
                currentGameState = GameState::GAMEOVER;
            }
        }

        //Reset the last move timer
        timeSinceLastMove = sf::Time::Zero;
    }//END of if statement
}

void Engine::draw() {
    mParam->window->clear(sf::Color::Black);

    for (auto &w: wallSections) {
        mParam->window->draw(w.getShape());
    }

    mParam->window->draw(apple.getSprite());

    for (auto &s: snake) {
        mParam->window->draw(s.getShape());
    }

    mParam->window->draw(titleText);
    mParam->window->draw(currentLevelText);
    mParam->window->draw(applesEatenText);
    mParam->window->draw(scoreText);

    if (currentGameState == GameState::GAMEOVER) {
        mParam->window->draw(gameOverText);
        mParam->window->draw(pressSpaceText);
        mParam->window->draw(quitToMenuText);
    }

    mParam->window->display();
}

void Engine::input() {
    sf::Event event{};

    while (mParam->window->pollEvent(event)) {
        //Close window
        if (event.type == sf::Event::Closed) {
            mParam->window->close();
        }
        //keyboard input
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                mParam->window->close();
            }

            if (event.key.code == sf::Keyboard::Pause) {
                togglePause();
            }

            //New game
            if (currentGameState == GameState::GAMEOVER) {
                if (event.key.code == sf::Keyboard::Space) {
                    startTheGame();
                }
                if (event.key.code == sf::Keyboard::Q) {
                    saveData();
                    mParam->states->add(std::make_unique<MainMenu>(mParam));
                }
            }

            if (event.key.code == sf::Keyboard::Up) {
                addDirection(Direction::UP);
            } else if (event.key.code == sf::Keyboard::Down) {
                addDirection(Direction::DOWN);
            } else if (event.key.code == sf::Keyboard::Left) {
                addDirection(Direction::LEFT);
            } else if (event.key.code == sf::Keyboard::Right) {
                addDirection(Direction::RIGHT);
            }
        }
    }
}

void Engine::startTheGame() {

    score = 0;
    speed = 5;
    snakeDirection = Direction::RIGHT;
    timeSinceLastMove = sf::Time::Zero;

    sectionsToAdd = 0;
    directionQueue.clear();
    wallSections.clear();
    applesEatenThisLevel = 0;
    applesEatenTotal = 0;
    currentLevel = 1;
    loadLevel(currentLevel);
    newSnake();
    moveApple();
    currentGameState = GameState::RUNNING;
    lastGameState = currentGameState;
    currentLevelText.setString("level " + std::to_string(currentLevel));
    applesEatenText.setString("apples " + std::to_string(applesEatenTotal));
    sf::FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    applesEatenText.setPosition(sf::Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));
    scoreText.setString(std::to_string(score));
    sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setPosition(resolution.x - scoreTextBounds.width - 15, -9);
}

//load next level and reset the Snake
void Engine::beginNextLevel() {
    currentLevel += 1;
    wallSections.clear();
    directionQueue.clear();
    speed = 2 + currentLevel;
    snakeDirection = Direction::RIGHT;
    sectionsToAdd = 0;
    applesEatenThisLevel = 0;

    loadLevel(currentLevel);
    newSnake();
    moveApple();
    currentLevelText.setString("level " + std::to_string(currentLevel));
    sf::FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    applesEatenText.setPosition(sf::Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));

}

//new Snake at the beginning of a level;
void Engine::newSnake() {
    snake.clear();
    snake.emplace_back(sf::Vector2f(100, 100));
    snake.emplace_back(sf::Vector2f(80, 100));
    snake.emplace_back(sf::Vector2f(60, 100));
}

//The tail of the Snake, to elongate the body
void Engine::addSnake() {
    sf::Vector2f newSectionPosition = snake[snake.size() - 1].getPosition();
    snake.emplace_back(newSectionPosition);
}

void Engine::moveApple() {
    //Find a location to place the Apple(not inside Snake/Wall)

    //Divide the field into sections the size of the Apple - except the walls
    sf::Vector2f appleResolution = sf::Vector2f(resolution.x / 20 - 2, resolution.y / 20 - 2);
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
        for (auto &s: snake) {
            if (s.getShape().getGlobalBounds().intersects(
                    sf::Rect<float>(newAppleLocation.x, newAppleLocation.y, 20, 20))) {
                badLocation = true;
                break;
            }
        }

        //check if its in the Wall
        for (auto &w: wallSections) {
            if (w.getShape().getGlobalBounds().intersects(
                    sf::Rect<float>(newAppleLocation.x, newAppleLocation.y, 20, 20))) {
                badLocation = true;
                break;
            }
        }

    } while (badLocation);
    apple.setPosition(newAppleLocation);
}

void Engine::togglePause() {
    if (currentGameState == GameState::RUNNING) {
        lastGameState = currentGameState;
        currentGameState = GameState::PAUSED;
    } else if (currentGameState == GameState::PAUSED) {
        currentGameState = lastGameState;
    }
}

void Engine::setupText(sf::Text *textItem, const sf::Font &font, const sf::String &value, int size, sf::Color colour) {
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
            maxLevels++;
        }
    }
}

//checks a level from a file and converts 'x' characters to add Wall
void Engine::loadLevel(int levelNumber) {
    std::string levelFile = levels[levelNumber - 1];
    std::ifstream level(levelFile);
    std::string line;
    if (level.is_open()) {
        for (int y = 0; y < 30; y++) {
            getline(level, line);
            for (int x = 0; x < 40; x++) {
                if (line[x] == 'x') {
                    wallSections.emplace_back(Wall(sf::Vector2f(x * 20, y * 20), sf::Vector2f(20, 20)));
                }
            }
        }
    }
    level.close();
}

void Engine::saveData() {
    //load previous data

    std::ifstream saveFileProfile("assets/save/dataProfile.txt");
    int a;//apples
    size_t highScore;
    int TotalApples;
    if (saveFileProfile.is_open()) {
        saveFileProfile >> a >> highScore >> TotalApples;
        std::cout << a << " " << highScore << " " << TotalApples << std::endl;
        saveFileProfile.close();
    }

    //store new + old data
    std::ofstream saveProfile("assets/save/dataProfile.txt");
    if (saveProfile.is_open()) {
        saveProfile << a + applesEatenTotal << std::endl;
        if (highScore < score)
            saveProfile << score << std::endl;
        else saveProfile << highScore << std::endl;

        if (TotalApples < applesEatenTotal) {
            saveProfile << applesEatenTotal;
        } else saveProfile << TotalApples;
        std::cout << a + applesEatenTotal << " " << score << std::endl;
        saveFileProfile.close();
    }
}

void Engine::addDirection(int newDirection) {
    if (directionQueue.empty()) {
        directionQueue.emplace_back(newDirection);
    } else {
        if (directionQueue.back() != newDirection) {
            directionQueue.emplace_back(newDirection);
        }
    }
}