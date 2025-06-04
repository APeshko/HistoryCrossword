#include "../include/StateManager.h"

StateManager::StateManager(sf::RenderWindow& window) : window(window) {}

void StateManager::changeState(std::unique_ptr<State> state) {
    state->setManager(this);
    currentState = std::move(state);
}

void StateManager::handleEvent(const sf::Event& event) {
    if (currentState) {
        currentState->handleEvent(event);
    }
}

void StateManager::update(float dt) {
    if (currentState) {
        currentState->update(dt);
    }
}

void StateManager::draw() {
    if (currentState) {
        currentState->draw(window);
    }
}
