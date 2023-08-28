#include "Game.h"
#include "MainMenu.h"


Game::Game() : mParam(std::make_shared<Param>()) {
    mParam->window->create(sf::VideoMode(800, 600), "Snake2", sf::Style::Close);
    mParam->states->add(std::make_unique<MainMenu>(mParam));

    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (mParam->window->isOpen()) {
        timeSinceLastFrame += clock.restart();

        while (timeSinceLastFrame > SECONDS_PER_FRAME) {
            timeSinceLastFrame -= SECONDS_PER_FRAME;

            mParam->states->stateChange();
            mParam->states->getCurrent()->input();
            mParam->states->getCurrent()->update(SECONDS_PER_FRAME);
            mParam->states->getCurrent()->draw();
        }
    }
}

Game::~Game() {}
