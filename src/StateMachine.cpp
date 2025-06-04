#include "StateMachine.h"

void StateMachine::pushState(std::unique_ptr<State> state) {
    states.push(std::move(state));
    states.top()->onEnter();
}

void StateMachine::popState() {
    if (!states.empty()) {
        states.top()->onExit();
        states.pop();
    }
}

void StateMachine::changeState(std::unique_ptr<State> state) {
    if (!states.empty()) {
        states.top()->onExit();
        states.pop();
    }
    states.push(std::move(state));
    states.top()->onEnter();
}

State* StateMachine::getCurrentState() {
    return states.empty() ? nullptr : states.top().get();
}

void StateMachine::handleEvent(const sf::Event& event) {
    if (!states.empty()) {
        states.top()->handleEvent(event);
    }
}

void StateMachine::update(float dt) {
    if (!states.empty()) {
        states.top()->update(dt);
    }
}

void StateMachine::render(sf::RenderWindow& window) {
    if (!states.empty()) {
        states.top()->render(window);
    }
}
