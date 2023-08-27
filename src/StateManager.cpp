#include "StateManager.h"

StateManager::StateManager() : mAdd(false), mDelete(false), mReplace(false) {}

StateManager::~StateManager() {}


void StateManager::pop() {
    mDelete = true;
}

void StateManager::add(std::unique_ptr<State> toAdd, bool replace) {
    mAdd = true;
    mNewState = std::move(toAdd);
    mReplace = replace;
}

void StateManager::stateChange() {
    if (mAdd){
        if (mReplace && (!mStateStack.empty())){
            mStateStack.pop();
            mReplace = false;
        }

        if (!mStateStack.empty()){
            mStateStack.top()->pause();
        }

        mStateStack.push(std::move(mNewState));
        mStateStack.top()->start();
        mAdd = false;
    }

    if (mDelete && (!mStateStack.empty())){
        mStateStack.pop();

        if (!mStateStack.empty()){
            mStateStack.top()->start();
        }
    }
}

std::unique_ptr<State> &StateManager::getCurrent() {
    return mStateStack.top();
}