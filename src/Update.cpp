#include "Engine.h"

void Engine::update() {
    //Update Snake position
    if (timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds()) {
        Vector2f thisSectionPosition = snake[0].getPosition();
        Vector2f lastSectionPosition = thisSectionPosition;

        //
        if (!directionQueue.empty()) {
            //Make sure the Snake doesn't go into apposite direction
            switch (snakeDirection) {
                case Direction::UP:
                    if (directionQueue.front() != Direction::DOWN) {
                        snakeDirection = directionQueue.front();

                    }
                    break;
                case Direction::DOWN:
                    if (directionQueue.front() != Direction::UP) {
                        snakeDirection = directionQueue.front();

                    }
                    break;
                case Direction::LEFT:
                    if (directionQueue.front() != Direction::RIGHT) {
                        snakeDirection = directionQueue.front();

                    }
                    break;
                case Direction::RIGHT:
                    if (directionQueue.front() != Direction::LEFT) {
                        snakeDirection = directionQueue.front();

                    }
                    break;
            }
            directionQueue.pop_front();
        }

        //Update Score
        score += snake.size() + (applesEatenTotal + 1);
        scoreText.setString(to_string(score));
        FloatRect scoreTextBounds = scoreText.getLocalBounds();
        scoreText.setPosition(resolution.x - scoreTextBounds.width - 15, -9);

        //Do we need to grow the Snake
        if (sectionsToAdd) {
            addSnake();
            sectionsToAdd--;
        }

        //Update snakes head position
        switch (snakeDirection) {
            case Direction::RIGHT:
                snake[0].setPosition(Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
                break;
            case Direction::DOWN:
                snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
                break;
            case Direction::LEFT:
                snake[0].setPosition(Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
                break;
            case Direction::UP:
                snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
                break;
        }

        //Update Snake tail position
        for (size_t s = 1; s < snake.size(); s++) {
            thisSectionPosition = snake[s].getPosition();
            snake[s].setPosition(lastSectionPosition);
            lastSectionPosition = thisSectionPosition;
        }

        // update Snake functions
        for (auto &s: snake) {
            s.update();
        }

        //Collision detection with Apple
        if (snake[0].getShape().getGlobalBounds().intersects(apple.getSprite().getGlobalBounds())) {
            applesEatenThisLevel += 1;
            applesEatenTotal += 1;
            applesEatenText.setString("apples " + to_string(applesEatenTotal));
            FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
            applesEatenText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));

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
                //We hit the Apple, increase speed/Snake size
                sectionsToAdd += 4;
                speed++;
                moveApple();
            }
        }

        //collision with Snake body
        for (size_t s = 1; s < snake.size(); s++) {
            if (snake[0].getShape().getGlobalBounds().intersects(snake[s].getShape().getGlobalBounds())) {
                //game over
                currentGameState = GameState::GAMEOVER;
            }
        }

        //Collision with Wall
        for (auto &w: wallSections) {
            if (snake[0].getShape().getGlobalBounds().intersects(w.getShape().getGlobalBounds())) {
                //Game over
                currentGameState = GameState::GAMEOVER;
            }
        }

        //Reset the last move timer
        timeSinceLastMove = Time::Zero;
    }//END of if statement

}
