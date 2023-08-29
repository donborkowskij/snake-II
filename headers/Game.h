#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "StateManager.h"

struct Param {
    std::unique_ptr<StateManager> states;
    std::unique_ptr<sf::RenderWindow> window;

    Param() {
        states = std::make_unique<StateManager>();
        window = std::make_unique<sf::RenderWindow>();
    }
};

class Game {
public:
    Game();

    ~Game();

    void run();

private:
    const sf::Time SECONDS_PER_FRAME = sf::seconds(1.f / 60.f);
    std::shared_ptr<Param> mParam;
};
