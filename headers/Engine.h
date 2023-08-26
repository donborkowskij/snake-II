#pragma once

#include "Snake.h"
#include "Apple.h"
#include "Wall.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <deque>
#include <fstream>
#include "MainMenu.h"
#include "Achievements.h"

using namespace sf;
using namespace std;

class Engine {
public:
    enum Direction {
        UP, RIGHT, DOWN, LEFT
    };
    enum GameState {
        RUNNING, PAUSED, GAMEOVER
    };

    Engine();

    static void setupText(Text *textItem, const Font &font, const String &value, int size, Color colour);
    void input();
    void addDirection(int newDirection);
    void update();
    void draw();
    void newSnake();
    void addSnake();
    void moveApple();
    void checkLevelFiles();
    void loadLevel(int levelNumber);
    void beginNextLevel();
    void startTheGame();
    void togglePause();
    void saveData();
    void run();
    void runMenu();

private:
    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;

    vector<Snake> snake;

    int snakeDirection;
    deque<int> directionQueue;
    int speed;
    int sectionsToAdd;
    int applesEatenThisLevel;
    int applesEatenTotal;
    unsigned long long int score;

    Apple apple;

    vector<Wall> wallSections;
    int currentLevel;
    int maxLevels;
    vector<String> levels;

    Font mainFont;
    Text titleText;
    Text applesEatenText;
    Text currentLevelText;
    Text scoreText;
    Text gameOverText;
    Text pressSpaceText;
    Text quitToMenuText;

    Time timeSinceLastMove;

    int currentGameState;
    int lastGameState;
};
