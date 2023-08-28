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
#include "State.h"


class Engine : public State {
public:
    enum Direction {
        UP, RIGHT, DOWN, LEFT
    };
    enum GameState {
        RUNNING, PAUSED, GAMEOVER
    };

    Engine(std::shared_ptr<Param> param);

    void update(const sf::Time &deltaTime) override;

    void draw() override;

    void input() override;

    static void
    setupText(sf::Text *textItem, const sf::Font &font, const sf::String &value, int size, sf::Color colour);

//    void input();

    void addDirection(int newDirection);

//    void update();

//    void draw();

    void newSnake();

    void addSnake();

    void moveApple();

    void checkLevelFiles();

    void loadLevel(int levelNumber);

    void beginNextLevel();

    void startTheGame();

    void togglePause();

    void saveData();

//    void run();

private:
    std::shared_ptr<Param> mParam;
    sf::Vector2f resolution;
//    RenderWindow window;
    const unsigned int FPS = 60;
    static const sf::Time TimePerFrame;

    std::vector<Snake> snake;

    int snakeDirection;
    std::deque<int> directionQueue;
    int speed;
    int sectionsToAdd;
    int applesEatenThisLevel;
    int applesEatenTotal;
    unsigned long long int score;

    Apple apple;

    std::vector<Wall> wallSections;
    int currentLevel;
    int maxLevels;
    std::vector<sf::String> levels;

    sf::Font mFont;
    sf::Text titleText;
    sf::Text applesEatenText;
    sf::Text currentLevelText;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Text pressSpaceText;
    sf::Text quitToMenuText;

    sf::Time timeSinceLastMove;

    int currentGameState;
    int lastGameState;

    sf::Clock clock;
    sf::Time dt;
};
