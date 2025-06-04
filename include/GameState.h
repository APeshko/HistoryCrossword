#pragma once
#include "State.h"
#include "Crossword.h"
#include <SFML/Graphics.hpp>

class GameState : public State {
public:
    GameState(StateMachine& machine, sf::RenderWindow& window, int level);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    void onEnter() override;
    void onExit() override;

private:
    void createCrossword(int level);
    void setupUI();

    StateMachine& machine;
    sf::RenderWindow& window;
    int currentLevel;
    std::unique_ptr<Crossword> crossword;
    sf::Text levelText;
    sf::Text backButton;
    sf::Text checkButton;
    sf::Text resultText;
    sf::RectangleShape background;
};
