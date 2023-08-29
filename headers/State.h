#pragma once

#include <SFML/System/Time.hpp>

class State {
public:
    State() {};

    virtual ~State() {};

    virtual void update(const sf::Time &deltaTime) = 0;

    virtual void draw() = 0;

    virtual void input() = 0;

    virtual void pause() {};

    virtual void start() {};
};
