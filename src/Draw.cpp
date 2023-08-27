#include "Engine.h"

void Engine::draw() {
    window.clear(Color::Black);

    //draw Wall
    for (auto &w: wallSections) {
        window.draw(w.getShape());
    }

    //Draw Apple
    window.draw(apple.getSprite());

    //Draw Snake
    for (auto &s: snake) {
        window.draw(s.getShape());
    }

    //Draw text
    window.draw(titleText);
    window.draw(currentLevelText);
    window.draw(applesEatenText);
    window.draw(scoreText);

    //Draw game over
    if (currentGameState == GameState::GAMEOVER) {
        window.draw(gameOverText);
        window.draw(pressSpaceText);
        window.draw(quitToMenuText);
    }

    window.display();
}