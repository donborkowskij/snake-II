//
// Created by donat on 5/30/2021.
//

#ifndef FIRSTPROG_ENGINE_H
#define FIRSTPROG_ENGINE_H

#include "Snake.h"
#include "Apple.h"
#include "Wall.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <deque>
#include <fstream>

using namespace sf;
using namespace std;

class Engine {
private:

    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = 60;
    static const Time TimePerFrame;

    vector<Snake> snake;

    int snakeDirection;
    deque<int> directionQueue; //queue for direction key presses
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

    Time timeSinceLastMove;

    int currentGameState;
    int lastGameState; // for storing the last state the game was in

public:
    enum Direction{ UP, RIGHT, DOWN, LEFT};
    enum GameState {RUNNING, PAUSED, GAMEOVER};
    Engine();
    void input();
    void addDirection(int newDirection);
    void update();
    void draw();

    static void setupText(Text *textItem, const Font &font, const String &value, int size, Color colour);

    void newSnake();
    void addSnake();

    void moveApple();
    void checkLevelFiles();
    void loadLevel(int levelNumber);

    void beginNextLevel();
    void startTheGame();

    void togglePause();

    void run();

};


#endif //FIRSTPROG_ENGINE_H
