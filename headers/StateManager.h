#pragma once

#include <stack>
#include <memory>
#include "State.h"

class StateManager {
public:
    StateManager();

    ~StateManager();

    void pop();

    void add(std::unique_ptr<State> toAdd, bool replace = false);

    void stateChange();

    std::unique_ptr<State> &getCurrent();

private:
    bool mAdd;
    bool mDelete;
    bool mReplace;

    std::stack<std::unique_ptr<State>> mStateStack;
    std::unique_ptr<State> mNewState;
};
