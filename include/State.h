#pragma once
#include <SFML/Graphics.hpp>

class StateMachine;

class State {
public:
    virtual ~State() = default;
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void onEnter() {}
    virtual void onExit() {}
};
