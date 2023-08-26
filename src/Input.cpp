#include "Engine.h"

void Engine::input() {
    Event event{};

    while (window.pollEvent(event)) {
        //Close window
        if (event.type == Event::Closed) {
            window.close();
        }
        //keyboard input
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Escape) {
                window.close();
            }

            //pause
            if (event.key.code == Keyboard::Pause) {
                togglePause();
            }

            //New game
            if (currentGameState == GameState::GAMEOVER) {
                if (event.key.code == Keyboard::Space) {
                    startTheGame();
                }
                if (event.key.code == Keyboard::Q) {
                    saveData();
//                    runMenu();
                }
            }

            //Direction
            if (event.key.code == Keyboard::Up) {
                addDirection(Direction::UP);
            } else if (event.key.code == Keyboard::Down) {
                addDirection(Direction::DOWN);
            } else if (event.key.code == Keyboard::Left) {
                addDirection(Direction::LEFT);
            } else if (event.key.code == Keyboard::Right) {
                addDirection(Direction::RIGHT);
            }
        }
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
