//
// Created by donat on 5/30/2021.
//

#include "Engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine(){
    resolution = Vector2f(800,600);
    window.create(VideoMode(resolution.x, resolution.y), "Snake", Style::Default);
    window.setFramerateLimit(FPS);
    maxLevels = 0;
    checkLevelFiles();

    startTheGame();

    mainFont.loadFromFile("assets/fonts/slant_regular.ttf");
    setupText(&titleText, mainFont, "Snake", 28, Color::Blue);
    FloatRect titleTextBounds = titleText.getLocalBounds();
    titleText.setPosition(Vector2f( resolution.x / 2 - titleTextBounds.width / 2, -9));

    setupText(&currentLevelText, mainFont, "level 1", 28, Color::Blue);
    currentLevelText.setPosition(Vector2f(15, -9));
    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();

    setupText(&applesEatenText, mainFont, "apples 0", 28, Color::Blue);
    applesEatenText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width +20, -9));

    setupText(&scoreText, mainFont, to_string(score), 28, Color::Blue);
    FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setPosition(resolution.x - scoreTextBounds.width -15, -9);

    setupText(&gameOverText, mainFont, "GAME OVER", 72, Color::Yellow);
    FloatRect  gameOverTextBounds= gameOverText.getLocalBounds();
    gameOverText.setPosition(Vector2f(resolution.x / 2 - gameOverTextBounds.width / 2, 100));
    gameOverText.setOutlineColor(Color::Black);
    gameOverText.setOutlineThickness(2);

    setupText(&pressSpaceText, mainFont, "Press SPACE to try again", 38, Color::Green);
    FloatRect pressSpaceTextBounds = pressSpaceText.getLocalBounds();
    pressSpaceText.setPosition(Vector2f(resolution.x / 2 - pressSpaceTextBounds.width / 2 , 200));
    pressSpaceText.setOutlineColor(Color::Black);
    pressSpaceText.setOutlineThickness(2);

}

void Engine::startTheGame(){
    score = 0;
    speed = 2;
    snakeDirection= Direction::RIGHT;
    timeSinceLastMove = Time::Zero;

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
    currentLevelText.setString("level " + to_string(currentLevel));
    applesEatenText.setString("apples " + to_string(applesEatenTotal));
    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    applesEatenText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width +20, -9));
    scoreText.setString(to_string(score));
    FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setPosition(resolution.x - scoreTextBounds.width -15, -9);

}

//load next level and reset the snake
void Engine::beginNextLevel() {
    currentLevel +=1;
    wallSections.clear();
    directionQueue.clear();
    speed = 2 +currentLevel;
    snakeDirection = Direction::RIGHT;
    sectionsToAdd = 0;
    applesEatenThisLevel = 0;

    loadLevel(currentLevel);
    newSnake();
    moveApple();
    currentLevelText.setString("level " + to_string(currentLevel));
    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    applesEatenText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width +20, -9));

}

//new snake at the beginning of a level;
void Engine::newSnake() {
    snake.clear();
    snake.emplace_back(Vector2f(100,100));
    snake.emplace_back(Vector2f(80,100));
    snake.emplace_back(Vector2f(60,100));

}
//The tail of the Snake, to elongate the body
void Engine::addSnake() {
    Vector2f newSectionPosition = snake[snake.size() - 1].getPosition();
    snake.emplace_back(newSectionPosition);
}

void Engine::moveApple() {
    //Find a location to place the apple(not inside snake/wall)

    //Divide the field into sections the size of the apple - except the walls
    Vector2f appleResolution = Vector2f(resolution.x / 20 - 2, resolution.y /20 -2);
    Vector2f newAppleLocation;
    bool badLocation = false;
    srand(time(nullptr));
    //loop to find good locations
    do {
        badLocation = false;
        //generate random location
        newAppleLocation.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleResolution.x)) *20;
        newAppleLocation.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleResolution.y)) *20;

        //check if it's in the snake
        for(auto & s : snake) {
            if (s.getShape().getGlobalBounds().intersects(Rect<float>(newAppleLocation.x, newAppleLocation.y, 20 , 20))){
                badLocation = true;
                break;
            }
        }

        //check if its in the wall
        for (auto & w : wallSections) {
            if (w.getShape().getGlobalBounds().intersects(Rect<float>(newAppleLocation.x, newAppleLocation.y, 20 , 20))) {
                badLocation = true;
                break;
            }
        }

    } while (badLocation);
        apple.setPosition(newAppleLocation);
}

void Engine::togglePause() {
    if(currentGameState == GameState::RUNNING){
        lastGameState = currentGameState;
        currentGameState = GameState::PAUSED;
    }
    else if (currentGameState == GameState::PAUSED) {
        currentGameState = lastGameState;
    }
}

void Engine::setupText(Text *textItem, const Font &font, const String &value, int size, Color colour) {
    textItem->setFont(font);
    textItem->setString(value);
    textItem->setCharacterSize(size);
    textItem->setFillColor(colour);

}

void Engine::checkLevelFiles() {
    //Load the levels file
    ifstream levelsManifest ("assets/levels/levels.txt");
    ifstream testFile;
    for (string manifestLine; getline(levelsManifest, manifestLine);){
        //check that the level file opens
        testFile.open("assets/levels/" + manifestLine);
        if  (testFile.is_open()){
            //the file opens -> add to the list of levels
            levels.emplace_back("assets/levels/" + manifestLine);
            testFile.close();
            maxLevels++;
        }
    }
}

//checks a level from a file and converts 'x' characters to add wall
void Engine::loadLevel(int levelNumber) {
    string levelFile = levels[levelNumber - 1];
    ifstream level (levelFile);
    string line;
    if (level.is_open()) {
        for (int y = 0; y <30; y++) {
            getline(level, line);
            for (int x = 0; x<40; x ++) {
                if (line[x] == 'x') {
                    wallSections.emplace_back(Wall(Vector2f(x * 20, y *20),Vector2f(20, 20)));
                }
            }
        }
    }
    level.close();
}

void Engine::run(){
    Clock clock;

    //Main loop
    while (window.isOpen()){
        Time dt = clock.restart();

        if(currentGameState == GameState::PAUSED || currentGameState== GameState::GAMEOVER){
            //if paused, check for input to unpause later and continue
            input();

            //Game Over
            if (currentGameState == GameState::GAMEOVER){
                draw();
            }
            sleep(milliseconds(2));
            continue;
        }

        timeSinceLastMove += dt;

        input();
        update();
        draw();
    }
}