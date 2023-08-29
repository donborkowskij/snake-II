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
    Engine(std::shared_ptr<Param> param);

    void update(const sf::Time &deltaTime) override;

    void draw() override;

    void input() override;

private:
    static void setupText(sf::Text *textItem,
                          const sf::Font &font,
                          const sf::String &value,
                          int size,
                          sf::Color colour);

    void addDirection(int newDirection);

    void newSnake();

    void addSnake();

    void moveApple();

    void checkLevelFiles();

    void loadLevel(int levelNumber);

    void beginNextLevel();

    void startTheGame();

    void togglePause();

    void saveData() const;

    void handleDirectionChange();

    void updateScore();

    void updateSnake(sf::Vector2f thisSectionPosition,
                     sf::Vector2f lastSectionPosition);

    void collisionWithApple();

    void collisionGameOver();

    void toggleGameOver();

    enum Direction {
        UP, RIGHT, DOWN, LEFT
    };
    enum GameState {
        RUNNING, PAUSED, GAMEOVER
    };

    std::shared_ptr<Param> mParam;
    sf::Vector2f mResolution;
    static const sf::Time mTimePerFrame;
    sf::Time mTimeSinceLastMove;

    std::vector<Snake> mSnake;
    int mSnakeDirection;
    std::deque<int> mDirectionQueue;
    int mSpeed;
    int mSectionsToAdd;
    int mApplesEatenThisLevel;
    int mApplesEatenTotal;
    unsigned long long int mScore;

    Apple mApple;
    std::vector<Wall> mWallSections;

    int mCurrentLevel;
    int mMaxLevels;
    std::vector<sf::String> mLevels;

    sf::Font mFont;
    sf::Text mTitleText;
    sf::Text mApplesEatenText;
    sf::Text mCurrentLevelText;
    sf::Text mScoreText;
    sf::Text mGameOverText;
    sf::Text mPressSpaceText;
    sf::Text mQuitToMenuText;

    int mCurrentGameState;
    int mLastGameState;
};
