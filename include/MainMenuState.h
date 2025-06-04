#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>

class MainMenuState : public State {
public:
    MainMenuState(StateMachine& machine, sf::RenderWindow& window);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    void onEnter() override;
    void onExit() override;

private:
    StateMachine& machine;
    sf::RenderWindow& window;
    sf::Text title;
    sf::Text level1Button;
    sf::Text level2Button;
    sf::Text level3Button;
    sf::Text exitButton;
    sf::RectangleShape background;
};
